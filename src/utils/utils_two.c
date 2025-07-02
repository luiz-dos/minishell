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
