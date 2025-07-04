/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:17 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:24:01 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	g_sig;

t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}

bool	ft_get_input(t_shell *data)
{
	char	*input;
	char	*pwd;

	pwd = color_to_prompt(get_pathname());
	input = readline(pwd);
	free(pwd);
	if (input == NULL)
		free_exit(data, EXIT_SUCCESS);
	if (input[0] == 0 || only_space(input))
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
		if (ft_get_input(data))
		{
			input_analizes(data);
			ft_tokenclear(data->tokens);
			clean_cmd_list(data->commands);
			if (data->input)
				free(data->input);
			data->tokens = NULL;
			data->commands = NULL;
			data->input = NULL;
			set_sig_main();
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	(void)av;
	g_sig = 0;
	if (!*envp)
	{
		shell()->envvar = min_env();
		shell()->envvar_export = create_lst_export();
		remove_envvar(&shell()->envvar_export, "_");
	}
	else
	{
		shell()->envvar = create_lst_envvar(envp);
		shell()->envvar_export = create_lst_export();
		remove_envvar(&shell()->envvar_export, "_");
	}
	set_sig_main();
	sort_var(shell()->envvar_export);
	set_shlvl(shell());
	set_questionvar(shell(), 0);
	loop_those_shells(shell());
	return (0);
}
