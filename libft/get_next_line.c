/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:13:55 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/09/11 16:36:13 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* check if BUFFER_SIZE > INT_MAX
* check if the file can be opened
* check if it has not reached FOPEN_MAX
* check if fd < 0
* check if BUFFER_SIZE <= 0
* read the file, create a line,
		put the rest in the static variable for the next call
* while the line is not created, continue reading (put a flag)
*/
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	int			found_newline;

	if (BUFFER_SIZE > 2147483647 || fd >= FOPEN_MAX || fd < 0
		|| BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	found_newline = 0;
	while (!found_newline && (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0))
	{
		line = ft_line(line, buffer);
		ft_handle_buffer(buffer, &found_newline);
	}
	return (line);
}
