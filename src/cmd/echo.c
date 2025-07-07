/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:24 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/06 17:21:35 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

bool	is_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	mini_echo(char	**args, int fd)
{
	bool	flag_nl;
	int		i;

	if (!args)
		return ;
	flag_nl = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
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
