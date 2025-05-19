/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:28:47 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:39:22 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_specifier(t_str *data, t_data_format *data_f, va_list args)
{
	if (data_f->cspecs->c)
		print_char(data, data_f, va_arg(args, int));
	else if (data_f->cspecs->s)
		print_string(data, data_f, va_arg(args, char *));
	else if (data_f->cspecs->p)
		print_pointer(data, data_f, va_arg(args, unsigned long long int));
	else if (data_f->cspecs->d || data_f->cspecs->i)
		print_int(data, data_f, va_arg(args, int));
	else if (data_f->cspecs->u)
		print_unsigned_int(data, data_f, va_arg(args, unsigned int));
	else if (data_f->cspecs->x || data_f->cspecs->upper_x)
		print_hex(data, data_f, va_arg(args, unsigned long long int));
}
