/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:20:20 by gufreire          #+#    #+#             */
/*   Updated: 2025/05/23 19:21:49 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

t_shell *shell(void)
{
	static t_shell shell;
	
	return (&shell);
}

t_var	*env(void)
{
	static t_var	env;

	return (&env);
}

t_command	*cmmd(void)
{
	static t_command	cmmd;

	return (&cmmd);
}

t_tokens	*input(void)
{
	static t_tokens	input;

	return (&input);
}