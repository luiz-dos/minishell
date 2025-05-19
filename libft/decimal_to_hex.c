/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:20:57 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:27:13 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*decimal_to_hex_two(t_data_format *data_f, char *hex,
		unsigned long long int num)
{
	int	tmp;
	int	i;

	i = 0;
	while (num != 0)
	{
		tmp = num % 16;
		if (tmp < 10)
			hex[i] = tmp + 48;
		else
		{
			if (data_f->cspecs->x || data_f->cspecs->p)
				hex[i] = tmp + 87;
			else
				hex[i] = tmp + 55;
		}
		num = num / 16;
		i++;
	}
	hex[i] = '\0';
	return (hex);
}

char	*decimal_to_hex(t_data_format *data_f, unsigned long long int num,
		unsigned long long int len_num)
{
	char	*hex;

	hex = (char *)malloc((len_num + 1) * sizeof(char));
	if (!hex)
		return (NULL);
	if (num == 0)
	{
		hex[0] = '0';
		hex[1] = '\0';
	}
	else
		hex = decimal_to_hex_two(data_f, hex, num);
	return (hex);
}
