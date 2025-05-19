#include "../inc/libs.h"

int	global_sig;

t_shell *ft_start_shell(void)
{
	static t_shell shell;
	return (&shell);
}

bool    ft_get_input(t_shell *data)
{
	char	*input;
	char	*pwd;
	
	pwd = color_to_prompt(get_pathname());
	input = readline("minishell$ ");
	free(pwd);
	if (input == NULL) // crtl+D faz o readline retonar NULL, entao fecha o minishell
	{
		free_exit(data);
		exit(EXIT_SUCCESS);
	}
	if (input[0] == 0 || only_space(input)) /* input somente espaco devolve um novo prompt */
	{
		free(input);
		return (false);
	}
	if (input)
	{
		add_history(input);
		data->input = ft_strdup(input);
		free(input);
	}
	return (true);
}

int	ainput(t_shell *data)
{
	char	**input;

	input = ft_split(data->input, ' ');
	if (!input)
		return (1);
	if (ft_strcmp(input[0], "env") == 0)
		mini_env(data->envvar);
	else if (ft_strcmp(input[0], "export") == 0)
		print_export(data);
	else if (ft_strcmp(input[0], "exit") == 0)
	{
		free_array(input);
		free_exit(data);
		return (1);
	}
	else if (ft_strcmp(input[0], "cd") == 0)
		cd(data, input);
	else if (ft_strcmp(input[0], "unset") == 0)
		unset(data, input);
	else if (ft_strcmp(input[0], "pwd") == 0)
		mini_pwd(data);
	else if (ft_strcmp(input[0], "echo") == 0)
		mini_echo(input, 1);
	// else
	// 	commands(data, input);
	free_array(input);
	return (0);
}

static void loop_those_shells(t_shell *data)
{
	while (1)
	{
		if(ft_get_input(data))
		{
			ft_input_analizes(data);
			// if (ainput(data))
			// 	break ;
			ft_tokenclear(data->tokens);
			clean_cmd_list(data->commands);
			free(data->input);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	t_shell	*data;

	if (ac != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	(void)av;
	global_sig = 0;
	data = ft_start_shell();
	ft_config_signals(0);
	data->envvar = create_lst_envvar(envp);
	data->envvar_export = create_lst_export(data);
	sort_var(data->envvar_export);
	set_shlvl(data);
	set_questionvar(data);
	data->std_fileno[0] = -1;
	data->std_fileno[1] = -1;
	loop_those_shells(data);
	return (0);
}
/*
 * 
 *
*/