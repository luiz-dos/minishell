/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:26:14 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:25:31 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_hex_fminus(t_data_format *data_f, char *str_num, int whitespace)
{
	if (data_f->flags->hash)
		print_0x(data_f);
	while (data_f->precision > (int)ft_strlen(str_num))
	{
		print_zero_byte(data_f);
		data_f->precision--;
	}
	ft_putstr_reverse_fd(str_num, 1);
	while (whitespace-- > 0)
		print_space_byte(data_f);
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_hex_fzero(t_data_format *data_f, char *str_num, int whitespace)
{
	if (data_f->flags->zero && data_f->precision > 0)
		print_hex_only(data_f, str_num, whitespace);
	else
	{
		if (data_f->flags->hash)
			print_0x(data_f);
		while (whitespace-- > 0)
			print_zero_byte(data_f);
		ft_putstr_reverse_fd(str_num, 1);
		data_f->bytes += (int)ft_strlen(str_num);
	}
}

void	print_hex_only(t_data_format *data_f, char *str_num, int whitespace)
{
	while (whitespace-- > 0)
		print_space_byte(data_f);
	if (data_f->flags->hash)
		print_0x(data_f);
	while (data_f->precision > (int)ft_strlen(str_num))
	{
		print_zero_byte(data_f);
		data_f->precision--;
	}
	ft_putstr_reverse_fd(str_num, 1);
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_hex_two(t_data_format *data_f, char *str_num, int whitespace)
{
	if (data_f->flags->hash && data_f->flags->zero)
		print_hex_fzero(data_f, str_num, whitespace);
	else if (data_f->flags->hash && data_f->flags->minus)
		print_hex_fminus(data_f, str_num, whitespace);
	else if (data_f->flags->hash)
		print_hex_only(data_f, str_num, whitespace);
	else if (data_f->flags->minus)
		print_hex_fminus(data_f, str_num, whitespace);
}
