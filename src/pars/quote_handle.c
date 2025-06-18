#include "../../inc/libs.h"

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
