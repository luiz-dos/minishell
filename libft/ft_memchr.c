/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:23:39 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:23:41 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* man
memchr: is used to find the first occurrence of a byte in a memory region.
Both "c" and the bytes of the memory area pointed to by "s" are interpreted
as unsigned char.
The memchr() and memrchr() functions return a pointer to the matching byte 
or NULL if the character does not occur in the given memory area.
s: pointer to memory region
c: value of the byte you want to search
n: number of bytes to be examined*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		pc;

	p = s;
	pc = (unsigned char)c;
	while (n-- > 0)
	{
		if (*p == pc)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
