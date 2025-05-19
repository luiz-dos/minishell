/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:04 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:29:05 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_noprecision(t_data_format *data_f, char *s)
{
	int	whitespace;

	whitespace = data_f->field_w - (int)ft_strlen(s);
	if (data_f->flags->minus)
	{
		ft_putstr_fd(s, 1);
		while (whitespace-- > 0)
			print_space_byte(data_f);
	}
	else
	{
		while (whitespace-- > 0)
			print_space_byte(data_f);
		ft_putstr_fd(s, 1);
	}
	data_f->bytes += (int)ft_strlen(s);
}

void	print_fprecision_two(t_data_format *data_f, char *s, int whitespace)
{
	int	i;

	i = 0;
	if (data_f->flags->minus)
	{
		while (data_f->precision > i && s[i])
		{
			ft_putchar_fd(s[i], 1);
			i++;
		}
		while (whitespace-- > 0)
			print_space_byte(data_f);
	}
	else
	{
		while (whitespace-- > 0)
			print_space_byte(data_f);
		while (data_f->precision > i && s[i])
		{
			ft_putchar_fd(s[i], 1);
			i++;
		}
	}
	data_f->bytes += i;
}

void	print_fprecision(t_data_format *data_f, char *s, t_bool str_null)
{
	int	whitespace;

	whitespace = get_whitespace(data_f, s);
	if (str_null == B_FALSE)
		print_fprecision_two(data_f, s, whitespace);
	else
	{
		if (data_f->precision >= (int)ft_strlen(s))
			print_fprecision_two(data_f, s, whitespace);
		else
		{
			while (data_f->field_w)
			{
				print_space_byte(data_f);
				data_f->field_w--;
			}
		}
	}
}

void	precision_is_zero(t_data_format *data_f)
{
	if (data_f->precision == 0)
	{
		while (data_f->field_w > 0)
		{
			print_space_byte(data_f);
			data_f->field_w--;
		}
	}
}

void	print_string(t_str *data, t_data_format *data_f, char *s)
{
	t_bool	str_null;

	str_null = B_FALSE;
	if (!s)
	{
		s = ft_strdup("(null)");
		str_null = B_TRUE;
	}
	if (s)
	{
		if (data_f->precision > 0)
			print_fprecision(data_f, s, str_null);
		else if (data_f->precision < 0)
			print_noprecision(data_f, s);
		else
			precision_is_zero(data_f);
	}
	if (str_null)
		free(s);
	data->bytes += data_f->bytes;
}
