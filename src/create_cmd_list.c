#include "../inc/libs.h"

void	handle_new_command(t_command **head, t_command **current, t_tokens *token)
{
	t_command	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_command));
	if (!new_cmd)
		return ;
	new_cmd->cmd = ft_strdup(token->content);
	new_cmd->args = ft_calloc(2, sizeof(char *));
	new_cmd->args[0] = ft_strdup(token->content);
	new_cmd->append = -1;
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

t_tokens	*handle_redir_in(t_command *cmd, t_tokens *token)
{
	if (!cmd || !token || !token->next)
		return (token);
	if (token->type == REDIR_IN)
		cmd->infile = ft_strdup(token->next->content);
	else if (token->type == HEREDOC)
	{
		cmd->has_heredoc = true;
		cmd->heredoc_delim = ft_strdup(token->next->content);
	}
	return (token->next);
}

t_tokens	*handle_redir_out(t_command *cmd, t_tokens *token)
{
	if (!cmd || !token || !token->next)
		return (token);
	cmd->outfile = ft_strdup(token->next->content);
	if (token->type == APPEND_OUT)
		cmd->append = 1;
	else
		cmd->append = 0;
	return(token->next);
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
		else if (tokens->type == REDIR_IN || tokens->type == HEREDOC)
			tokens = handle_redir_in(current_cmd, tokens);
		else if (tokens->type == REDIR_OUT || tokens->type == APPEND_OUT)
			tokens = handle_redir_out(current_cmd, tokens);
		else if (tokens->type == PIPE)
			current_cmd->has_pipe = true;
		tokens = tokens->next;
	}
	return (head);
}
