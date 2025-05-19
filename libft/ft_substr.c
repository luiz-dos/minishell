/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:11 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:48:12 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.
s: The string from which to create the substring.
start: The start index of the substring in the string ’s’.
len: The maximum length of the substring. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	if (s)
	{
		s_len = ft_strlen(s);
		if (start >= s_len)
			return (ft_strdup(""));
		if (len > (s_len - start))
			len = s_len - start;
		sub_str = (char *)malloc((len + 1) * sizeof(char));
		if (!sub_str)
			return (NULL);
		i = 0;
		while (i < len)
		{
			sub_str[i] = s[start];
			i++;
			start++;
		}
		sub_str[i] = '\0';
		return (sub_str);
	}
	return (NULL);
}
