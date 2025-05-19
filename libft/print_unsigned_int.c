/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:32 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:29:33 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_num_zero_two(t_data_format *data_f, unsigned int num)
{
	if (num == 0 && data_f->precision == 0)
	{
		precision_is_zero(data_f);
		data_f->error = B_TRUE;
	}
}

void	print_unsigned_int(t_str *data, t_data_format *data_f, unsigned int num)
{
	char	*str_num;

	str_num = ft_unsigned_itoa(num);
	handle_num_zero_two(data_f, num);
	if (data_f->flags->minus && !data_f->error)
	{
		if (data_f->flags->minus && data_f->flags->plus)
			print_fminus_fplus(data_f, str_num);
		else if (data_f->flags->minus && *str_num == '-')
			print_fminus_neg(data_f, str_num);
		else if (data_f->flags->minus && data_f->flags->space)
			print_fminus_fplus(data_f, str_num);
		else if (data_f->flags->minus && ft_isdigit(*str_num))
			print_fminus_posi(data_f, str_num);
	}
	if (!data_f->flags->minus && !data_f->error)
		print_int_two(data_f, str_num);
	data->bytes += data_f->bytes;
	free(str_num);
}
