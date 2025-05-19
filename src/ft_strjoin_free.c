#include "../inc/libs.h"

char	*ft_strjoin_free(const char *s1, const	char *s2)
{
	char	*str_join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str_join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_join)
		return (NULL);
	i = -1;
	while(s1[++i])
		str_join[i] = s1[i];
	j = -1;
	while(s2[++j])
		str_join[i++] = s2[j];
	str_join[i] = '\0';
	free((char *)s1);
	return (str_join);
}
