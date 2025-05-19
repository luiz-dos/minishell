/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:04 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:39:22 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_conversion(t_str *data, t_data_format *data_f)
{
	if (data->str[data->pos] == 'c')
		data_f->cspecs->c = B_TRUE;
	else if (data->str[data->pos] == 's')
		data_f->cspecs->s = B_TRUE;
	else if (data->str[data->pos] == 'p')
		data_f->cspecs->p = B_TRUE;
	else if (data->str[data->pos] == 'd')
		data_f->cspecs->d = B_TRUE;
	else if (data->str[data->pos] == 'i')
		data_f->cspecs->i = B_TRUE;
	else if (data->str[data->pos] == 'u')
		data_f->cspecs->u = B_TRUE;
	else if (data->str[data->pos] == 'x')
		data_f->cspecs->x = B_TRUE;
	else if (data->str[data->pos] == 'X')
		data_f->cspecs->upper_x = B_TRUE;
}
