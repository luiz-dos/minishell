#include "../../inc/libs.h"

int	ft_quote_checker(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dq % 2 == 0)
			sq++;
		else if (str[i] == '"' && sq % 2 == 0)
			dq++;
		i++;
	}
	if (sq % 2 != 0 || dq % 2 != 0)
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (0);
	}
	return (1);
}

int	inside_quotes(char	*str, size_t index)
{
	char	c;

	c = 0;
	if (!str || index > ft_strlen(str))
		return (0);
	while (*str && index--)
	{
		if (!c)
		{
			if (*str == '\'' || *str == '\"')
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	if (c == *str)
		c = 0;
	return ((c == '\'') + ((c == '\"') * 2));
}
