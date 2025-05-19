/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:21:30 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 13:26:42 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_numlen_two(unsigned int n)
{
	unsigned int	len;
	unsigned int	temp;

	temp = n;
	len = 0;
	if (temp <= 0)
	{
		len = 1;
		temp = -temp;
	}
	while (temp > 0)
	{
		len++;
		temp = temp / 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_numlen_two(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	str[len--] = '\0';
	while (len >= i)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
