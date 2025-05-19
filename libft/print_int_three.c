/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:26:46 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:25:55 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_fplus_plus(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	if (data_f->precision > (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - (int)ft_strlen(str_num);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
		while (data_f->field_w > (data_f->precision + 1))
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
	}
	else
	{
		ft_putstr_fd(str_num, 1);
		count_bytes = (data_f->field_w - ((int)ft_strlen(str_num)) - 1);
		while (count_bytes-- > 0)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_fminus_posi(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	if (data_f->precision > (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - (int)ft_strlen(str_num);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
		while (data_f->field_w > data_f->precision)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
	}
	else
	{
		ft_putstr_fd(str_num, 1);
		count_bytes = (data_f->field_w - (int)ft_strlen(str_num));
		while (count_bytes-- > 0)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_fminus_neg(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	if (*str_num == '-' && data_f->precision >= (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - ((int)ft_strlen(str_num) - 1);
		ft_putchar_fd('-', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(++str_num, 1);
		while (data_f->field_w > (data_f->precision + 1))
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
		data_f->bytes++;
	}
	else if (*str_num == '-' && data_f->precision < (int)ft_strlen(str_num))
	{
		count_bytes = (int)ft_strlen(str_num);
		ft_putstr_fd(str_num, 1);
		while (data_f->field_w > count_bytes++)
			print_space_byte(data_f);
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_fminus_fplus(t_data_format *data_f, char *str_num)
{
	if (data_f->flags->minus && ft_isdigit(*str_num))
	{
		if (data_f->flags->space && !data_f->flags->plus)
		{
			print_space_byte(data_f);
			print_fplus_plus(data_f, str_num);
		}
		else
		{
			print_plus_byte(data_f);
			print_fplus_plus(data_f, str_num);
		}
	}
	else if (data_f->flags->minus && *str_num == '-')
		print_fminus_neg(data_f, str_num);
	else if (data_f->flags->minus && ft_isdigit(*str_num))
	{
		print_space_byte(data_f);
		print_fplus_plus(data_f, str_num);
	}
}
