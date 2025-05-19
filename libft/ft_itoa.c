/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:12:14 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/16 16:12:15 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a string representing 
the integer received as an argument. Negative numbers must be handled*/
/*I count the number of digits, allocate space for the number of digits, 
if it is negative I add the '-' in position 0 of the str and 
transform the number into positive. I add the null character 
to the end of the str and move back one position. 
To add the digits to the str, I divide it by 10 
and take its modulus and add it from the end of the str to the beginning. 
Finally I return to str.*/
static int	ft_numlen(int n)
{
	int	len;
	int	temp;

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

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_numlen(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	str[len--] = '\0';
	while (len >= i)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
