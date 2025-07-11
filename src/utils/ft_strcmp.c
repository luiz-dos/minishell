/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:59:12 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 17:59:13 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	p1;
	unsigned char	p2;
	size_t			i;

	i = 0;
	if (!*s1 || !*s2)
		return (-1);
	while (s1[i] || s2[i])
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];
		if (p1 != p2)
			return (p1 - p2);
		i++;
	}
	return (0);
}
