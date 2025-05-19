/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:28:39 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 17:53:52 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long int	ft_numlen_three(unsigned long long int n)
{
	unsigned long long int	len;
	unsigned long long int	temp;

	temp = n;
	len = 0;
	if (temp == 0)
		len = 1;
	while (temp > 0)
	{
		len++;
		temp = temp / 10;
	}
	return (len);
}

void	print_pointer_two(t_data_format *data_f, char *num_hex, int whitespace)
{
	if (data_f->flags->minus)
	{
		print_0x(data_f);
		ft_putstr_reverse_fd(num_hex, 1);
		while (whitespace-- > 0)
			print_space_byte(data_f);
		data_f->bytes += (int)ft_strlen(num_hex);
	}
	else
	{
		while (whitespace-- > 0)
			print_space_byte(data_f);
		print_0x(data_f);
		ft_putstr_reverse_fd(num_hex, 1);
		data_f->bytes += (int)ft_strlen(num_hex);
	}
}

void	print_pointer(t_str *data, t_data_format *data_f,
		unsigned long long int num)
{
	char					*num_hex;
	int						whitespace;
	unsigned long long int	len_num;

	len_num = ft_numlen_three(num);
	if (num)
	{
		whitespace = 0;
		num_hex = decimal_to_hex(data_f, num, len_num);
		if (data_f->field_w > ((int)ft_strlen(num_hex) + 2))
		{
			whitespace = data_f->field_w - ((int)ft_strlen(num_hex) + 2);
			print_pointer_two(data_f, num_hex, whitespace);
		}
		else
			print_pointer_two(data_f, num_hex, whitespace);
		data->bytes += data_f->bytes;
		free(num_hex);
	}
	else
		print_string(data, data_f, "(nil)");
}
