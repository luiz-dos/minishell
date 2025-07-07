/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:23 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:24:19 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	handle_sigint_main(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_questionvar(shell(), 130);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	printf("\n");
	close(STDIN_FILENO);
}

void	set_sig_main(void)
{
	signal(SIGINT, handle_sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_heredoc(void)
{
	g_sig = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
