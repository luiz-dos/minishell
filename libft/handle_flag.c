/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:27 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:22:30 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_flag(t_str *data, t_data_format *data_f)
{
	while (data->str[data->pos] == ' ')
	{
		data_f->flags->space = B_TRUE;
		data->pos++;
	}
	while (data->str[data->pos] == '-')
	{
		data_f->flags->minus = B_TRUE;
		data->pos++;
	}
	while (data->str[data->pos] == '+')
	{
		data_f->flags->plus = B_TRUE;
		data->pos++;
	}
	while (data->str[data->pos] == '#')
	{
		data_f->flags->hash = B_TRUE;
		data->pos++;
	}
	while (data->str[data->pos] == '0')
	{
		data_f->flags->zero = B_TRUE;
		data->pos++;
	}
}
