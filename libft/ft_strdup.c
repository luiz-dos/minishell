/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:01 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:39:02 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strdup() function returns a pointer to a new string which is
a duplicate of the string s. Memory for the new string is obtained
with malloc(3), and can be freed with free(3).*/
char	*ft_strdup(const char *s)
{
	int		lenght;
	int		i;
	char	*dest;

	lenght = (int)ft_strlen(s);
	dest = (char *)malloc((lenght + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
