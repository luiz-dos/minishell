/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:25:15 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/24 10:54:50 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The  memcpy()  function  copies  n bytes from memory area
src to memory area dest.  The memory areas must not overlap.*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	if (src == dest)
		return (NULL);
	p_dest = (char *)dest;
	p_src = (char *)src;
	while (n-- > 0)
		*p_dest++ = *p_src++;
	return (dest);
}
