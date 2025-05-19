/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fzero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:47 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:25:48 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_fzero_fspace(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	if (*str_num == '-')
	{
		count_bytes = data_f->field_w - (int)ft_strlen(str_num);
		ft_putchar_fd('-', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(++str_num, 1);
		data_f->bytes++;
	}
	else if (ft_isdigit(*str_num))
	{
		print_space_byte(data_f);
		count_bytes = data_f->field_w - ((int)ft_strlen(str_num) + 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_fzero_fplus(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	if (ft_isdigit(*str_num))
	{
		count_bytes = data_f->field_w - ((int)ft_strlen(str_num) + 1);
		ft_putchar_fd('+', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	else if (*str_num == '-')
	{
		count_bytes = data_f->field_w - ((int)ft_strlen(str_num));
		ft_putchar_fd('-', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(++str_num, 1);
	}
	data_f->bytes += ((int)ft_strlen(str_num) + 1);
}

void	print_fzero_only(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	count_bytes = (data_f->field_w - (int)ft_strlen(str_num));
	if (ft_isdigit(*str_num))
	{
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	else if (*str_num == '-')
	{
		ft_putchar_fd('-', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(++str_num, 1);
		data_f->bytes++;
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_fzero(t_data_format *data_f, char *str_num)
{
	if (data_f->flags->zero && data_f->precision > 1)
	{
		data_f->flags->zero = B_FALSE;
		print_int_two(data_f, str_num);
	}
	else
	{
		if (data_f->flags->zero && data_f->flags->plus)
			print_fzero_fplus(data_f, str_num);
		else if (data_f->flags->zero && data_f->flags->space)
			print_fzero_fspace(data_f, str_num);
		else if (data_f->flags->zero)
			print_fzero_only(data_f, str_num);
	}
}
