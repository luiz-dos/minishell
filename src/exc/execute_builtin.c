/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:01 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:19:19 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_shell *data, t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "env") == 0)
		mini_env(cmd->args);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		mini_export(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		mini_exit(cmd->args);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		cd(data, cmd->args);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		unset(data, cmd->args);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		mini_pwd(data);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		mini_echo(cmd->args, 1);
}
