/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:21 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:13:10 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	handle_new_command(t_command **head, t_command **current,
	t_tokens *token)
{
	t_command	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_command));
	if (!new_cmd)
		return ;
	new_cmd->cmd = ft_strdup(token->content);
	new_cmd->args = ft_calloc(2, sizeof(char *));
	new_cmd->args[0] = ft_strdup(token->content);
	new_cmd->heredoc_fd = -1;
	new_cmd->next = NULL;
	if (!*head)
		*head = new_cmd;
	else
		(*current)->next = new_cmd;
	*current = new_cmd;
}

void	handle_argument(t_command *cmd, t_tokens *token)
{
	int		i;
	char	**new_args;

	if (!cmd || !token)
		return ;
	i = 0;
	while (cmd->args[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		i++;
	}
	new_args[i] = ft_strdup(token->content);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

t_tokens	*handle_redir(t_command *cmd, t_tokens *token)
{
	t_redir		*new;
	t_redir		*last;

	if (!cmd || !token || !token->next)
		return (token);
	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (token->next);
	new->type = token->type;
	new->filename = ft_strdup(token->next->content);
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (token->next);
}

t_command	*create_cmd_list(t_tokens *tokens)
{
	t_command	*head;
	t_command	*current_cmd;

	head = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (tokens->type == CMD)
			handle_new_command(&head, &current_cmd, tokens);
		else if (tokens->type == ARG)
			handle_argument(current_cmd, tokens);
		else if (tokens->type >= HEREDOC && tokens->type <= REDIR_IN)
			tokens = handle_redir(current_cmd, tokens);
		else if (tokens->type == PIPE)
			current_cmd->has_pipe = true;
		tokens = tokens->next;
	}
	return (head);
}
