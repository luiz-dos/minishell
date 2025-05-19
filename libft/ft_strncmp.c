/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:44:12 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:44:13 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strcmp() function compares the two strings s1 and s2.
The comparison is done using unsigned characters.

if s1 is greater, it returns an integer greater than 0. 
if it is smaller, it returns an integer less than 0 and 
if s1 and s2 are equal, it returns 0. */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	p1;
	unsigned char	p2;
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];
		if (p1 != p2)
			return (p1 - p2);
		i++;
	}
	return (0);
}
