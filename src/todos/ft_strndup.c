#include "../inc/libs.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

    if (!s)
		return (NULL);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
