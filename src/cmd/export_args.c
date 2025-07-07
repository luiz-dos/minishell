/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:30 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:13:24 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	check_value(t_command *cmd, char **var_name, char **var_value, int i)
{
	if (ft_strchr(cmd->args[i], '=') == NULL)
	{
		*var_name = ft_strdup(cmd->args[i]);
		*var_value = NULL;
	}
	else
	{
		*var_name = ft_strdup_two(cmd->args[i], '=');
		*var_value = ft_strdup(ft_strchr(cmd->args[i], '=') + 1);
	}
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	not_valid(t_command *cmd, int i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->args[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	set_questionvar(shell(), 1);
}

void	check_var_name(t_command *cmd, char *var_name, char *var_value, int i)
{
	int	valid;

	valid = is_valid_identifier(var_name);
	if (valid == 0)
		not_valid(cmd, i);
	else
		set_envvar(shell(), var_name, var_value, 1);
	free_str(var_name, var_value);
}

void	mini_export(t_command *cmd)
{
	int		i;
	char	*var_name;
	char	*var_value;

	if (count_args(cmd->args) == 1)
		print_export(shell());
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			var_name = NULL;
			var_value = NULL;
			check_value(cmd, &var_name, &var_value, i);
			if (var_name && var_name[0] == '#')
			{
				free_str(var_name, var_value);
				break ;
			}
			check_var_name(cmd, var_name, var_value, i);
			i++;
		}
	}
}
