/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:59 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:29:38 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	close_remaining_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_str(char *var_name, char *var_value)
{
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}
