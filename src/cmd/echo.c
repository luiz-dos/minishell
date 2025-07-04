/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:24 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 17:57:25 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	mini_echo(char	**args, int fd)
{
	bool	flag_nl;
	int		i;

	if (!args)
		return ;
	flag_nl = false;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		flag_nl = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag_nl)
		ft_putchar_fd('\n', fd);
	set_questionvar(shell(), 0);
}
