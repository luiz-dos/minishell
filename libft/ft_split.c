/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:34:37 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:34:38 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.*/
static int	ft_count_str(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (count);
}

static int	ft_strlen_split(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static char	*ft_strdup_split(char *str, char c)
{
	char	*dest;
	int		len_word;
	int		i;

	i = 0;
	len_word = ft_strlen_split(str, c);
	dest = (char *)malloc(len_word * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (i < len_word)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	fill_array(char **array_str, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			array_str[i] = ft_strdup_split((char *)s, c);
			if (!array_str[i])
			{
				while (i-- >= 0)
					free(array_str[i]);
				free(array_str);
				return (0);
			}
			while (*s && (*s != c))
				s++;
			i++;
		}
	}
	array_str[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array_str;

	if (s)
	{
		array_str = (char **)malloc((ft_count_str((char *)s, c) + 1)
				* sizeof(char *));
		if (!array_str)
			return (NULL);
		if ((fill_array(array_str, s, c)) == 0)
			return (NULL);
		return (array_str);
	}
	return (NULL);
}
