/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:51 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:39:52 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a new string,
which is the result of the concatenation of ’s1’ and ’s2’*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		i;

	if (s1 && s2)
	{
		new_string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
				* sizeof(char));
		if (!new_string)
			return (NULL);
		i = 0;
		while (*s1)
		{
			new_string[i++] = *s1;
			s1++;
		}
		while (*s2)
		{
			new_string[i++] = *s2;
			s2++;
		}
		new_string[i] = '\0';
		return (new_string);
	}
	return (NULL);
}
