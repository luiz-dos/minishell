/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analizes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:30 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:26:58 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	execute_commands(t_command *cmd)
{
	if (cmd->has_pipe)
		handle_pipeline(cmd);
	else
		single_command(cmd);
}

void	input_analizes(t_shell *data)
{
	char	**tokens;
	char	*normalized;

	if (ft_quote_checker(data->input))
	{
		expand_dolar(&data->input);
		normalized = normalize_input(data->input);
		if (!normalized)
			return ;
		free(data->input);
		data->input = normalized;
		mark_input(data->input);
		tokens = ft_split(data->input, N_SPACE);
		if (!tokens)
			return ;
		create_tokens(tokens);
		if (check_tokens(data))
		{
			data->commands = create_cmd_list(data->tokens);
			if (data->commands)
				execute_commands(data->commands);
		}
	}
}
