/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:54 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:17:45 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

char	*create_envvar_content(char *name, char *value)
{
	char	*content;

	content = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!content)
		return (NULL);
	ft_strcpy(content, name);
	ft_strcpy(content + ft_strlen(name), "=");
	ft_strcpy(content + ft_strlen(name) + 1, value);
	return (content);
}

void	update_envvar(t_var *envvar, char *name, char *value)
{
	free(envvar->name);
	free(envvar->value);
	free(envvar->content);
	envvar->name = ft_strdup(name);
	envvar->value = ft_strdup(value);
	envvar->content = create_envvar_content(name, value);
	if (envvar->value != NULL)
		envvar->env = true;
	envvar->exp = true;
}

void	add_new_envvar(t_var *lst, char *name, char *value, int flag)
{
	t_var	*envvar;

	envvar = ft_calloc(1, sizeof(t_var));
	if (!envvar)
		return ;
	envvar->content = create_envvar_content(name, value);
	if (!envvar->content)
	{
		free (envvar);
		return ;
	}
	if (flag == 1)
	{
		envvar->env = true;
		envvar->exp = true;
	}
	else
	{
		envvar->env = false;
		envvar->exp = true;
	}
	envvar->name = ft_strdup(name);
	envvar->value = ft_strdup(value);
	add_var_back(&lst, envvar);
}

void	set_envvar(t_shell *data, char *name, char *value, int flag)
{
	t_var	*envvar;
	t_var	*export_var;

	envvar = find_envvar(data->envvar, name);
	if (envvar && value)
		update_envvar(envvar, name, value);
	else if (!envvar && !value)
		add_new_envvar(data->envvar, name, value, 0);
	else if (!envvar)
		add_new_envvar(data->envvar, name, value, flag);
	export_var = find_envvar(data->envvar_export, name);
	if (export_var && value)
		update_envvar(export_var, name, value);
	else if (!export_var)
		add_new_envvar(data->envvar_export, name, value, flag);
}
