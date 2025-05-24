#include "../../inc/libs.h"

void	ft_set_token_type(t_tokens *lst)
{
	t_tokens	*current;

	current = lst;
	while (current)
	{
		if (ft_strcmp(current->content, ">") == 0)
			current->type = REDIR_OUT;
		else if (ft_strcmp(current->content, ">>") == 0)
			current->type = APPEND_OUT;
		else if (ft_strcmp(current->content, "<") == 0)
			current->type = REDIR_IN;
		else if (ft_strcmp(current->content, "<<") == 0)
			current->type = HEREDOC;
		else if (ft_strcmp(current->content, "|") == 0)
			current->type = PIPE;
		else if (!current->prev || (current->prev->type == PIPE))
			current->type = CMD;
		else if (current->prev->type == HEREDOC)
			current->type = DELIM;
		else if (current->prev->type >= APPEND_OUT)
			current->type = FILENAME;
		else
			current->type = ARG;
		current = current->next;
	}
}
