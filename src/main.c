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
	
	pwd = get_pathname();
	input = readline(pwd);
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

void	loop_those_shells(t_shell *data)
{
	while (1)
	{
		if(ft_get_input(data))
		{
			ft_input_analizes(data);
			ft_tokenclear(data->tokens);
			clean_cmd_list(data->commands);
			free(data->input);
			data->tokens = NULL;
			data->commands = NULL;
			data->input = NULL;
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
 * TODO (expand_envvar): Alocar "expanded" aos poucos, de acordo com o tamanho das expansoes para evitar overflow
 * TODO: quotes ainda nao esta 100% indentico ao bash (add whitespace no input \2 \3 )
 * TODO: criar funcoes para lidar com escapes \
 * 
*/