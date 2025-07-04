/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:40 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:10:25 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

bool	check_options(char *option)
{
	if (option[0] == '-')
	{
		printf("-minishell: %s : invalid option\n", option);
		return (true);
	}
	return (false);
}

void	remove_envvar(t_var **lst, char *var_name)
{
	t_var	*temp;

	if (!lst || !*lst || !var_name)
		return ;
	temp = find_envvar(*lst, var_name);
	if (!temp)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		*lst = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->content);
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	unset(t_shell *data, char **args)
{
	int	i;

	if (!args || !*args || !args[1])
		return ;
	if (check_options(args[1]))
		return ;
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
		{
			remove_envvar(&data->envvar, args[i]);
			remove_envvar(&data->envvar_export, args[i]);
		}
		i++;
	}
}
