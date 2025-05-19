/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:41:33 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/24 11:41:37 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memmove() function copies n bytes from memory area src
to memory area dest. The memory areas may overlap:
copying takes place as though the bytes in src are first
copied into a temporary array that does not overlap src or dest,
and the bytes are then copied from the temporary array to dest.*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (dest == src)
		return (NULL);
	if (n == 0)
		return (dest);
	if (dest > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}
