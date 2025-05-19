/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:14:15 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/06/07 13:56:14 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	return (len);
}
/*Allocate space for new line
 * Put what is already on the line on the new line
 * Put what was read on the new line (up to \n)
 * Free memory in the previous line to avoid memory leak
 * Returns newline to line
 */

char	*ft_line(char *line, char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = (char *)malloc(ft_strlen_gnl(line) + ft_strlen_gnl(buffer) + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	j = -1;
	while (buffer && buffer[++j])
	{
		new_line[i++] = buffer[j];
		if (buffer[j] == '\n')
			break ;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}
/*If there is something before "\n" set it to zero (because I already put it
on the new line)
* If you find "\n" it means that the new line has already been created
(then set the flag to 1)
* Arrange static variable for next call
*/

void	ft_handle_buffer(char *buffer, int *found_newline)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (*found_newline == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			*found_newline = 1;
		buffer[i] = 0;
		i++;
	}
}
