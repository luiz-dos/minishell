/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:11:16 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/06 20:11:24 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	create_cmd_list_two(t_command *current_cmd)
{
	if (current_cmd)
		current_cmd->has_pipe = true;
	current_cmd = NULL;
}
