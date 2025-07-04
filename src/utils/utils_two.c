/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:59:38 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 17:59:39 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	has_heredoc_redir(t_command *cmd)
{
	t_redir	*curr;

	if (!cmd->redirs)
		return (0);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	has_out_redir(t_command *cmd)
{
	t_redir	*curr;

	if (!cmd->redirs)
		return (0);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == REDIR_OUT || curr->type == APPEND_OUT)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	has_in_redir(t_command *cmd)
{
	t_redir	*curr;

	if (!cmd->redirs)
		return (0);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
			return (1);
		curr = curr->next;
	}
	return (0);
}
