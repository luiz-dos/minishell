/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:20:36 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/23 12:36:41 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	analyze_identifier_two(t_str *data, t_data_format *data_f)
{
	while (isflag(data->str[data->pos]))
		handle_flag(data, data_f);
	while (isflag(data->str[data->pos]))
		handle_flag(data, data_f);
	if (ft_isdigit(data->str[data->pos]))
		handle_field_width(data, data_f);
	while (data->str[data->pos] == '.')
		handle_precision(data, data_f);
}

void	analyze_identifier(t_str *data, va_list args)
{
	t_data_format	*data_f;

	data_f = NULL;
	data->pos++;
	data_f = init(data_f);
	analyze_identifier_two(data, data_f);
	if (isconversion(data->str[data->pos]))
	{
		handle_conversion(data, data_f);
		print_specifier(data, data_f, args);
	}
	else
	{
		ft_putstr_fd("Invalid specifier\n", 1);
		data->error = B_TRUE;
	}
	free(data_f->cspecs);
	free(data_f->flags);
	free(data_f);
}
