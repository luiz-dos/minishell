/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envvar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:56 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:15:56 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	set_shlvl(t_shell *data)
{
	t_var	*envvar;
	int		value;
	char	*str_value;

	envvar = find_envvar(data->envvar, "SHLVL");
	if (!envvar)
	{
		add_new_envvar(data->envvar, "SHLVL", "1", 0);
		add_new_envvar(data->envvar_export, "SHLVL", "1", 0);
		return ;
	}
	value = ft_atoi(envvar->value);
	if (value >= 999)
		set_envvar(data, "SHLVL", "1", 0);
	else
	{
		value++;
		str_value = ft_itoa(value);
		set_envvar(data, "SHLVL", str_value, 0);
		free(str_value);
	}
}

void	set_questionvar(t_shell *data, int return_status)
{
	t_var	*envvar;
	char	*str_value;

	envvar = find_envvar(data->envvar, "?");
	if (!envvar)
	{
		add_new_envvar(data->envvar, "?", "0", 0);
		add_new_envvar(data->envvar_export, "?", "0", 0);
	}
	else
	{
		data->return_status = return_status;
		str_value = ft_itoa(return_status);
		set_envvar(data, "?", str_value, 0);
		free(str_value);
	}
}

t_var	*min_env(void)
{
	char	**data;
	t_var	*ret;
	char	*pwd;

	data = (char **)(malloc)(5 * sizeof(char *));
	if (!data)
		return (NULL);
	pwd = getcwd(NULL, 0);
	data[0] = ft_strjoin("PWD=", pwd);
	data[1] = ft_strdup("SHLVL=1");
	data[2] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:\
		/usr/bin:/sbin:/bin");
	data[3] = ft_strdup("_=/usr/bin/env");
	data[4] = NULL;
	ret = create_lst_envvar(data);
	free(data);
	free(pwd);
	return (ret);
}
