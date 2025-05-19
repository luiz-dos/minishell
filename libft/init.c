/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:01 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:39:22 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_flags(t_data_format *data_f)
{
	data_f->flags = (t_flags *)malloc(sizeof(t_flags));
	if (!data_f->flags)
		return ;
	data_f->flags->minus = B_FALSE;
	data_f->flags->plus = B_FALSE;
	data_f->flags->hash = B_FALSE;
	data_f->flags->zero = B_FALSE;
	data_f->flags->space = B_FALSE;
}

void	init_cspecs(t_data_format *data_f)
{
	data_f->cspecs = (t_specs *)malloc(sizeof(t_specs));
	if (!data_f->cspecs)
		return ;
	data_f->cspecs->c = B_FALSE;
	data_f->cspecs->s = B_FALSE;
	data_f->cspecs->p = B_FALSE;
	data_f->cspecs->d = B_FALSE;
	data_f->cspecs->i = B_FALSE;
	data_f->cspecs->u = B_FALSE;
	data_f->cspecs->x = B_FALSE;
	data_f->cspecs->upper_x = B_FALSE;
	data_f->cspecs->percent = B_FALSE;
}

t_data_format	*init(t_data_format *data_f)
{
	data_f = (t_data_format *)malloc(sizeof(t_data_format));
	if (!data_f)
		return (NULL);
	data_f->field_w = 0;
	data_f->precision = -1;
	data_f->bytes = 0;
	data_f->error = B_FALSE;
	init_flags(data_f);
	init_cspecs(data_f);
	return (data_f);
}
