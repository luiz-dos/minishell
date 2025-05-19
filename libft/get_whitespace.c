/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_whitespace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:30:59 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/20 16:31:00 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_whitespace(t_data_format *data_f, char *s)
{
	int	whitespace;

	whitespace = 0;
	if (data_f->cspecs->s)
	{
		if (data_f->precision > (int)ft_strlen(s))
			whitespace = data_f->field_w - (int)ft_strlen(s);
		else if (data_f->precision <= (int)ft_strlen(s))
			whitespace = data_f->field_w - data_f->precision;
	}
	else
	{
		if (data_f->precision > (int)ft_strlen(s))
			whitespace = data_f->field_w - data_f->precision;
		else if (data_f->precision <= (int)ft_strlen(s))
			whitespace = data_f->field_w - (int)ft_strlen(s);
	}
	return (whitespace);
}
