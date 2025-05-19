/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:31:35 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:32:54 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putchar_percent(t_str *data)
{
	ft_putchar_fd(data->str[++data->pos], 1);
	data->bytes++;
}

void	print_plus_byte(t_data_format *data_f)
{
	ft_putchar_fd('+', 1);
	data_f->bytes++;
}

void	print_space_byte(t_data_format *data_f)
{
	ft_putchar_fd(' ', 1);
	data_f->bytes++;
}

void	print_zero_byte(t_data_format *data_f)
{
	ft_putchar_fd('0', 1);
	data_f->bytes++;
}

void	print_0x(t_data_format *data_f)
{
	if (data_f->cspecs->x || data_f->cspecs->p)
		ft_putstr_fd("0x", 1);
	else
		ft_putstr_fd("0X", 1);
	data_f->bytes += 2;
}
