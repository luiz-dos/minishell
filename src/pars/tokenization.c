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

char	*ft_gettoken(char **input)
{
	char	*start;
	char	*token;
	char	quote;
	int		len;

	while (**input && **input == ' ')
		(*input)++;
	if (**input == '\0')
		return (NULL);
	start = *input;
	quote = '\0';
	len = 0;
	while ((*input)[len])
	{
		if ((*input)[len] == '\'' || (*input)[len] == '\"')
			update_quote((*input)[len], &quote);
		else if ((*input)[len] == ' ' && quote == '\0')
			break ;
		len++;
	}
	token = ft_strndup(start, len);
	*input += len;
	return (token);
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
		node = ft_calloc(1, sizeof(t_tokens));
		node->content = token;
		node->type = -1;
		node->single_quotes = false;
		node->double_quotes = false;
		ft_tokenadd_back(&head, node);
	}
	data->tokens = head;
}

