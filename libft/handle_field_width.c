/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_field_width.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:15 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:28:17 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_field_width(t_str *data, t_data_format *data_f)
{
	int		len;
	int		i;
	char	*array_num;

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
	data_f->field_w = ft_atoi(array_num);
	free(array_num);
}
