/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:24:03 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:24:05 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The  memcmp()  function  compares the first n bytes 
(each interpreted as unsigned char) of the memory areas s1 and s2.
if s1 is greater, it returns an integer greater than 0. 
if it is smaller, it returns an integer less than 0 and 
if s1 and s2 are equal, it returns 0.
If n is zero, the return value is zero.*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n-- > 0)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
