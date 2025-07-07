/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:37 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 20:10:53 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	mini_pwd(t_shell	*data)
{
	char	*pwd;
	t_var	*pwd_envvar;

	pwd_envvar = find_envvar(data->envvar, "PWD");
	if (pwd_envvar)
	{
		printf("%s\n", pwd_envvar->value);
		set_questionvar(data, 0);
		return ;
	}
	else if (!pwd_envvar)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror(pwd);
			return ;
		}
		printf("%s\n", pwd);
		free(pwd);
		set_questionvar(data, 0);
	}
}
