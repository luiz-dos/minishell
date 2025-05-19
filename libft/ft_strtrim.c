/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:46:37 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:46:39 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
specified in ’set’ removed from the beginning and the end of the string. */

/* I start at the beginning of s1, compare whether the character is present
in s2, if so I move on to the next character in s1 until I find one that
is not present in s2.
I repeat the process, but I start at the end of s1 and go back to the
beginning until I find the character that is not part of s2.
I allocate memory to store the range characters (start - end) and
return this range */

static int	ft_char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		i;
	int		start;
	int		end;

	if (s1 && set)
	{
		start = 0;
		while (s1[start] && ft_char_in_set(s1[start], set))
			start++;
		end = ft_strlen(s1);
		while (end > start && ft_char_in_set(s1[end - 1], set))
			end--;
		new_str = (char *)malloc((end - start + 1) * sizeof(char));
		if (!new_str)
			return (NULL);
		i = 0;
		while (start < end)
		{
			new_str[i++] = s1[start++];
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}
