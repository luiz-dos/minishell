#include "../inc/libs.h"

char	ft_detect_and_skip_quote(char **src, t_tokens *node)
{
	char	quote;

	quote = **src;
	if (quote == '\'' || quote == '\"')
	{
		if (quote == '\'')
			node->single_quotes = true;
		else
			node->double_quotes = true;
		(*src)++;
		return (quote);
	}
	return (0);
}

void	ft_copy_until_quote(char **src, char **dst, char quote)
{
	while (**src && **src != quote)
	{
		**dst = **src;
		(*dst)++;
		(*src)++;
	}
	if (**src == quote)
		(*src)++;
}

void	ft_strip_quotes_loop(char **src, char **dst, t_tokens *node)
{
	char	q;

	while (**src)
	{
		if (**src == '\'' || **src == '\"')
		{
			q = ft_detect_and_skip_quote(src, node);
			ft_copy_until_quote(src, dst, q);
		}
		else
			*(*dst)++ = *(*src)++;
	}
	**dst = '\0';
}

void	ft_strip_quotes(t_tokens *node)
{
	char	*src;
	char	*dst;
	char	*clean;
	size_t	len;

	if (!node || !node->content)
		return ;
	len = ft_strlen(node->content);
	clean = ft_calloc(len + 1, sizeof(*clean));
	if (!clean)
		return ;
	node->single_quotes = false;
	node->double_quotes = false;
	src = node->content;
	dst = clean;
	ft_strip_quotes_loop(&src, &dst, node);
	free(node->content);
	node->content = clean;
}

void	strip_quotes_all(t_tokens *lst)
{
	while (lst)
	{
		ft_strip_quotes(lst);
		lst = lst->next;
	}
}

