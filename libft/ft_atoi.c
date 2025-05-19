/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:12:04 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/15 15:12:24 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* man
The  atoi() function converts the initial portion of the string 
pointedto by nptr to int.
The behavior is the same as "strtol(nptr, NULL, 10);" 
except that atoi() does not detect errors.
Return value: the converted value or 0 in case of error.*/
int	ft_atoi(const char *nptr)
{
	int	i;
	int	signal;
	int	result;

	i = 0;
	signal = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signal = -1;
		i++;
	}
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	return (result * signal);
}
