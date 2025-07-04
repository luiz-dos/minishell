/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:56 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:27:25 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

t_var	*find_envvar(t_var *lst, char *name)
{
	t_var	*current;

	if (!lst || !name)
		return (NULL);
	current = lst;
	while (current)
	{
		if (current->name && ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_value(t_shell *data, char *name)
{
	t_var	*envvar;
	char	*temp;

	envvar = find_envvar(data->envvar, name);
	if (!envvar)
		return (NULL);
	temp = envvar->value;
	return (temp);
}
