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

void	exec_external_cmd(char **cmd)
{
	char	*command_path;
	char	**env_var;

	env_var = envvar_array(shell()->envvar);
	if (!cmd[0] || only_space(cmd[0]) || check_envp(env_var))
	{
		free_array(env_var);
		exit(1);
	}
	command_path = get_command_path(cmd[0], env_var);
	if (!command_path)
	{
		ft_putstr_fd(" command not found\n", 2);
		// printf("minishell: %s: command not found\n", cmd[0]);
		free_array(env_var);
		exit(127);
	}
	execve(command_path, cmd, env_var);
	free_array(env_var);
	free(command_path);
	perror("execve");
	exit(1);
}
/*
 * TODO: verificar se o arg e /bin/ls , se sim, nao procurar em get_command_path e mandar assim para execve
*/