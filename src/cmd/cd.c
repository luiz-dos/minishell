/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:17 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 19:58:14 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

char	*get_dir(char *arg, int *flag_free)
{
	char	*dir;

	dir = ft_strdup(arg);
	*flag_free = 1;
	return (dir);
}

void	update_pwd(t_shell *data, char *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error using getcwd\n");
		return ;
	}
	if (ft_strcmp(dir, ".") == 0)
	{
		set_envvar(data, "OLDPWD", pwd, 1);
		free(pwd);
		return ;
	}
	oldpwd = get_value(data, "PWD");
	if (!oldpwd)
		set_envvar(data, "OLDPWD", oldpwd, 1);
	set_envvar(data, "PWD", pwd, 0);
	free(pwd);
}

void	change_dir(char *dir, int flag_free, t_shell *data)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		set_questionvar(data, 1);
		return ;
	}
	if (chdir(dir) == -1)
	{
		perror(dir);
		free(oldpwd);
		oldpwd = NULL;
		set_questionvar(data, 1);
	}
	else
	{
		set_envvar(data, "OLDPWD", oldpwd, 1);
		update_pwd(data, dir);
	}
	if (flag_free == 1)
		free(dir);
	if (oldpwd)
		free(oldpwd);
}

void	cd(t_shell *data, char **args)
{
	char	*dir;
	int		flag_free;

	dir = NULL;
	flag_free = 0;
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		set_questionvar(data, 1);
		return ;
	}
	if (!args[1] || ft_strcmp(args[1], "--") == 0)
	{
		dir = get_value(data, "HOME");
		if (!dir)
			printf("HOME not set\n");
	}
	else if (args[1])
		dir = get_dir(args[1], &flag_free);
	if (dir)
		change_dir(dir, flag_free, data);
	else
		set_questionvar(data, 1);
}
