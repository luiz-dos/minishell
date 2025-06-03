#include "../../inc/libs.h"

int global_sig;

bool    ft_get_input(t_shell *data)
{
	char	*input;
	char	*pwd;
	
	pwd = color_to_prompt(get_pathname());
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
	if (ac != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	(void)av;
	global_sig = 0;
	if (!*envp)
	{
		shell()->envvar = min_env();
		shell()->envvar_export = create_lst_export();
	}
	else
	{
		shell()->envvar = create_lst_envvar(envp);
		shell()->envvar_export = create_lst_export();
	}
	ft_config_signals(0);
	sort_var(shell()->envvar_export);
	set_shlvl(shell());
	set_questionvar(shell());
	shell()->std_fileno[0] = -1;
	shell()->std_fileno[1] = -1;
	loop_those_shells(shell());
	return (0);
}
/*
 * TODO (expand_envvar): Alocar "expanded" aos poucos, de acordo com o tamanho das expansoes para evitar overflow
 * TODO: quotes ainda nao esta 100% indentico ao bash (add whitespace no input \2 \3 ) ✅
 * TODO: criar funcoes para lidar com escapes \
 * TODO: cd sem nada diz que tem demasiados argumentos mas move para o HOME na mesma ✅
 * TODO: nao da para entrar no minishell quando ja dentro do minishell
 * TODO: tratar a criacao de uma nova variavel (export a=12)
 * TODO: salvar a raiz "/" em OLDPWD quando usar (cd) para voltar quando usar (cd -)
 * TODO: $A deve expandir a variavel e caso o conteudo for um comando executa-lo ✅
*/