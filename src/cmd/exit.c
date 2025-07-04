/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:26 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 17:57:27 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	is_numeric_arg(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(char **args)
{
	long	code;

	if (!args[1])
		free_exit(shell(), shell()->return_status);
	if (!is_numeric_arg(args[1]))
	{
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		free_exit(shell(), 2);
	}
	if (args[2])
	{
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		set_questionvar(shell(), 1);
		return ;
	}
	code = ft_atoi(args[1]);
	free_exit(shell(), (unsigned char)code);
}
