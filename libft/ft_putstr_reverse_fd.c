/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_reverse_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:40 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 17:29:59 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_reverse_fd(char *s, int fd)
{
	char	*end;

	end = s;
	while (*end)
		end++;
	while (--end >= s)
		write(fd, end, 1);
}
