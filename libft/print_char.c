/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:28 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:25:29 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char_field_w(t_data_format *data_f, char c)
{
	int	whitespace;

	whitespace = data_f->field_w - 1;
	if (data_f->flags->minus)
	{
		ft_putchar_fd(c, 1);
		data_f->bytes++;
		while (whitespace-- > 0)
			print_space_byte(data_f);
	}
	else
	{
		while (whitespace-- > 0)
			print_space_byte(data_f);
		ft_putchar_fd(c, 1);
		data_f->bytes++;
	}
}

void	print_char(t_str *data, t_data_format *data_f, char c)
{
	if (data_f->field_w > 0)
		print_char_field_w(data_f, c);
	else
	{
		ft_putchar_fd(c, 1);
		data_f->bytes++;
	}
	data->bytes += data_f->bytes;
}
