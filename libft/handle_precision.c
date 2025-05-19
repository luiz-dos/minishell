/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:56 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:27:46 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_precision(t_str *data, t_data_format *data_f)
{
	int		i;
	int		len;
	char	*array_num;

	data->pos++;
	len = data->pos;
	while (ft_isdigit(data->str[data->pos]))
		data->pos++;
	array_num = (char *)malloc(sizeof(char) * (data->pos - len) + 1);
	if (!array_num)
		return ;
	i = 0;
	while (len < data->pos)
	{
		array_num[i] = data->str[len];
		i++;
		len++;
	}
	array_num[i] = '\0';
	data_f->precision = ft_atoi(array_num);
	free(array_num);
}
