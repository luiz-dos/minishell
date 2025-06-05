#include "../../inc/libs.h"

t_tokens	*ft_tokenlast(t_tokens *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*curr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_tokenlast(*lst);
	curr->next = new;
	new->prev = curr;
}

char	*extract_literal(char **input)
{
	char	*start;

	start = *input;
	while (**input && **input != ' ' && **input != '\'' && **input != '"')
		(*input)++;
	return (ft_strndup(start, *input - start));
}

char	*ft_gettoken(char **input)
{
	char	*start;
	char	*token;
	char	quote;

	while (**input && **input == ' ')
		(*input)++;
	if (**input == '\0')
		return (NULL);
	if (**input == '\'' || **input == '"')
	{
		quote = **input;
		start = (*input);
		(*input)++;
		while (**input && **input != quote)
			(*input)++;
		if (**input == quote)
			(*input)++;
		token = ft_strndup(start, *input - start);
		return (token);
	}
	return (extract_literal(input));
}

void	ft_tokenization(t_shell *data)
{
	t_tokens	*node;
	t_tokens	*head;
	char		*token;
	char		*cursor;

	cursor = data->input;
	head = NULL;
	while ((token = ft_gettoken(&cursor)) != NULL)
	{
		if ((token[0] == '\'' && token[1] == '\'' && token[2] == '\0') ||
		(token[0] == '"' && token[1] == '"' && token[2] == '\0'))
			free(token);
		else
		{
			node = ft_calloc(1, sizeof(t_tokens));
			node->content = token;
			node->type = -1;
			node->single_quotes = false;
			node->double_quotes = false;
			ft_tokenadd_back(&head, node);
		}
	}
	data->tokens = head;
}

