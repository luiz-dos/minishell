#include "../../inc/libs.h"

char	**envvar_array(t_var *lst)
{
	t_var	*temp;
	char	**env_var;
	int		i;

	i = 0;
	temp = lst;
	while (temp)
	{
		if (temp->env)
			i++;
		temp = temp->next;
	}
	env_var = (char **)malloc((i + 1) * sizeof(char *));
	if (!env_var)
		return (NULL);
	temp = lst;
	i = -1;
	while (temp)
	{
		if (temp->env)
			env_var[++i] = ft_strdup(temp->content);
		temp = temp->next;
	}
	env_var[++i] = NULL;
	return (env_var);
}

char	*get_command_path(char *cmd, char **env_var)
{
	char	**all_paths;
	char	*current_path;
	char	*path;
	int		i;

	i = 0;
	while((ft_strnstr(env_var[i], "PATH", 4)) == NULL)
		i++;
	all_paths = ft_split(env_var[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		current_path = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin_free(current_path, cmd);
		if (((access(path, F_OK)) == 0) && ((access(path, X_OK)) == 0))
		{
			free_array(all_paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}

void	check_command(char *cmd)
{
	struct stat buf;

	if (stat(cmd, &buf) == 0)
	{
		if (buf.st_mode & __S_IFDIR && (ft_strncmp(cmd, "./", 2) == 0
				|| cmd[0] == '/'))
		{
			ft_putstr_fd(" Is a directory\n", 2);
			free_exit(shell(), 126);
		}
		else if (access(cmd, X_OK) != 0
			&& ft_strncmp(cmd, "./", 2) == 0)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			free_exit(shell(), 126);
		}
	}
	else
	{
		if (ft_strncmp(cmd, "./", 2) == 0 || cmd[0] == '/')
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			free_exit(shell(), 127);
		}
	}
}

void	exec_ext_cmd(char *command_path, char **cmd, char **env_var)
{
	if (!command_path)
	{
		ft_putstr_fd(" command not found\n", 2);
		// printf("minishell: %s: command not found\n", cmd[0]);
		free_exit(shell(), 127);
	}
	execve(command_path, cmd, env_var);
	free_array(env_var);
	free(command_path);
	perror("execve");
	free_exit(shell(), 1);
}

void	analize_ext_cmd(char **cmd)
{
	char	*command_path;

	shell()->ev_array = envvar_array(shell()->envvar);
	if (!cmd[0] || only_space(cmd[0]) || check_envp(shell()->ev_array))
		free_exit(shell(), 1);
	check_command(cmd[0]);
	if (ft_strncmp(cmd[0], "./", 2) == 0 || cmd[0][0] == '/')
		command_path = cmd[0];
	else
		command_path = get_command_path(cmd[0], shell()->ev_array);
	exec_ext_cmd(command_path, cmd, shell()->ev_array);
}
/*
 * TODO: verificar se o arg e /bin/ls , se sim, nao procurar em get_command_path e mandar assim para execve ✅
 * TODO: verificar permissao na hora de executar um programa, veficar se e um diretorio ✅
*/