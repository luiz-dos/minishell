#include "../inc/libs.h"

char	*ft_strdup_two(const char *s, char c)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s[i] != c)
		i++;
	dest = (char *)malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
