/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:26:26 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 15:55:11 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_hex(t_str *data, t_data_format *data_f, unsigned int num)
{
	unsigned long long int	len_num;
	int						whitespace;
	char					*str_num;

	if (num == 0 && data_f->precision == 0)
		precision_is_zero(data_f);
	else
	{
		if (num == 0 && data_f->flags->hash)
			data_f->flags->hash = B_FALSE;
		len_num = ft_numlen_three(num);
		str_num = decimal_to_hex(data_f, num, len_num);
		whitespace = get_whitespace(data_f, str_num);
		if (data_f->flags->hash)
			print_hex_two(data_f, str_num, (whitespace - 2));
		else if (data_f->flags->minus)
			print_hex_fminus(data_f, str_num, whitespace);
		else if (data_f->flags->zero)
			print_hex_fzero(data_f, str_num, whitespace);
		else
			print_hex_only(data_f, str_num, whitespace);
		free(str_num);
	}
	data->bytes += data_f->bytes;
}
