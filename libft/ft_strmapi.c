/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:42:20 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:42:22 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applies the function f to each character of the string s,
passing its index as the first argument and the character itself as the second.
A new string is created (using malloc(3)) to collect the results from the
successive applications of f */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*array_result;

	if (s && f)
	{
		len_s = ft_strlen(s);
		array_result = (char *)malloc((len_s + 1) * sizeof(char));
		if (!array_result)
			return (NULL);
		i = 0;
		while (i < len_s)
		{
			array_result[i] = f(i, s[i]);
			i++;
		}
		array_result[i] = '\0';
		return (array_result);
	}
	return (NULL);
}
