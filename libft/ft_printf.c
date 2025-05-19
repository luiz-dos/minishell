/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:31:46 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 15:26:59 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putchar_byte(t_str *data)
{
	ft_putchar_fd(data->str[data->pos], 1);
	data->bytes++;
}

void	ft_printf_two(t_str *data, va_list args)
{
	while (data->str[++data->pos] && !data->error)
	{
		if (data->str[data->pos] == '%' && !data->str[data->pos + 1])
			;
		else if (data->str[data->pos] == '%' && data->str[data->pos + 1]
			&& data->str[data->pos + 1] != '%')
			analyze_identifier(data, args);
		else if (data->str[data->pos] == '%' && data->str[data->pos + 1] == '%')
			putchar_percent(data);
		else
			putchar_byte(data);
	}
}

int	ft_printf(const char *format, ...)
{
	t_str	*data;
	va_list	args;
	int		bytes;

	if (!format)
		return (-1);
	va_start(args, format);
	data = (t_str *)malloc(sizeof(t_str));
	if (!data)
		return (1);
	data->pos = -1;
	data->bytes = 0;
	data->str = format;
	data->error = B_FALSE;
	ft_printf_two(data, args);
	bytes = data->bytes;
	va_end(args);
	free(data);
	return (bytes);
}
