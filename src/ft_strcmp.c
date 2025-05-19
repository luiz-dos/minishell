#include "../inc/libs.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	p1;
	unsigned char	p2;
	size_t			i;

	i = 0;
	while (s1[i] || s2[i])
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];
		if (p1 != p2)
			return (p1 - p2);
		i++;
	}
	return (0);
}
