/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:28:06 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:28:07 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_fplus_plus_two(t_data_format *data_f, char *str_num,
		int count_bytes)
{
	if (data_f->precision >= (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - (int)ft_strlen(str_num);
		while (data_f->field_w > (data_f->precision + 1))
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
		ft_putchar_fd('+', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	else if (data_f->precision < (int)ft_strlen(str_num))
	{
		count_bytes = (int)ft_strlen(str_num);
		while ((data_f->field_w - 1) > count_bytes++)
			print_space_byte(data_f);
		ft_putchar_fd('+', 1);
		ft_putstr_fd(str_num, 1);
	}
	data_f->bytes += ((int)ft_strlen(str_num) + 1);
}

void	print_posi(t_data_format *data_f, char *str_num, int count_bytes)
{
	if (data_f->precision > (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - (int)ft_strlen(str_num);
		while (data_f->field_w > data_f->precision)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	else
	{
		count_bytes = (data_f->field_w - (int)ft_strlen(str_num));
		while (count_bytes-- > 0)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
		ft_putstr_fd(str_num, 1);
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_neg(t_data_format *data_f, char *str_num, int count_bytes)
{
	if (*str_num == '-' && data_f->precision >= (int)ft_strlen(str_num))
	{
		count_bytes = data_f->precision - ((int)ft_strlen(str_num) - 1);
		while (data_f->field_w > (data_f->precision + 1))
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
		ft_putchar_fd('-', 1);
		while (count_bytes-- > 0)
			print_zero_byte(data_f);
		ft_putstr_fd(++str_num, 1);
		data_f->bytes++;
	}
	else if (*str_num == '-' && data_f->precision < (int)ft_strlen(str_num))
	{
		count_bytes = (int)ft_strlen(str_num);
		while (data_f->field_w > count_bytes++)
			print_space_byte(data_f);
		ft_putstr_fd(str_num, 1);
	}
	data_f->bytes += (int)ft_strlen(str_num);
}

void	print_no_fminus(t_data_format *data_f, char *str_num, int count_bytes)
{
	if (!data_f->flags->minus && ft_isdigit(*str_num))
	{
		if (data_f->flags->space && !data_f->flags->plus)
		{
			print_space_byte(data_f);
			data_f->field_w--;
			print_posi(data_f, str_num, count_bytes);
		}
		else
			print_fplus_plus_two(data_f, str_num, count_bytes);
	}
	else if (!data_f->flags->minus && *str_num == '-')
		print_neg(data_f, str_num, count_bytes);
}

void	print_int_two(t_data_format *data_f, char *str_num)
{
	int	count_bytes;

	count_bytes = 0;
	if (data_f->flags->zero)
		print_fzero(data_f, str_num);
	else if (data_f->flags->plus)
		print_no_fminus(data_f, str_num, count_bytes);
	else if (*str_num == '-')
		print_neg(data_f, str_num, count_bytes);
	else if (data_f->flags->space)
		print_no_fminus(data_f, str_num, count_bytes);
	else if (ft_isdigit(*str_num))
		print_posi(data_f, str_num, count_bytes);
}
