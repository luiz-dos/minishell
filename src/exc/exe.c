/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:59 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:20:04 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	cleanup_bkp(int stdin_bkp, int stdout_bkp)
{
	if (stdin_bkp != -1)
	{
		dup2(stdin_bkp, STDIN_FILENO);
		close(stdin_bkp);
		stdin_bkp = -1;
	}
	if (stdout_bkp != -1)
	{
		dup2(stdout_bkp, STDOUT_FILENO);
		close(stdout_bkp);
		stdout_bkp = -1;
	}
}

int	has_redir(t_command *cmd, int *stdin_bkp, int *stdout_bkp)
{
	if (has_in_redir(cmd) || has_heredoc_redir(cmd) || has_out_redir(cmd))
	{
		*stdin_bkp = dup(STDIN_FILENO);
		*stdout_bkp = dup(STDOUT_FILENO);
		if (*stdin_bkp == -1 || *stdout_bkp == -1)
		{
			perror("dup failed");
			if (*stdin_bkp != -1)
				close(*stdin_bkp);
			if (*stdout_bkp != -1)
				close(*stdout_bkp);
			*stdin_bkp = -1;
			*stdout_bkp = -1;
			return (-1);
		}
		if (handle_all_redirects(cmd) == -1)
		{
			cleanup_bkp(*stdin_bkp, *stdout_bkp);
			return (-1);
		}
		return (1);
	}
	return (0);
}

void	external_command(t_command *cmd, int *stdin_bkp, int *stdout_bkp,
	int redir_result)
{
	pid_t	pid;
	int		status;

	set_sig_ignore();
	pid = create_fork();
	if (pid == 0)
	{
		set_sig_child();
		analize_ext_cmd(cmd->args);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (redir_result == 1)
			cleanup_bkp(*stdin_bkp, *stdout_bkp);
		set_sig_main();
		if (WIFSIGNALED(status))
		{
			printf("\n");
			set_questionvar(shell(), (128 + WTERMSIG(status)));
		}
		else
			set_questionvar(shell(), WEXITSTATUS(status));
	}
}

void	single_command(t_command *cmd)
{
	int			stdin_bkp;
	int			stdout_bkp;
	int			redir_result;

	stdin_bkp = -1;
	stdout_bkp = -1;
	redir_result = has_redir(cmd, &stdin_bkp, &stdout_bkp);
	if (redir_result == -1)
		return ;
	if (is_builtin(cmd->cmd))
	{
		execute_builtin(shell(), cmd);
		if (redir_result == 1)
			cleanup_bkp(stdin_bkp, stdout_bkp);
	}
	else
		external_command(cmd, &stdin_bkp, &stdout_bkp, redir_result);
}

/* TODO: lidar com os redirects quando nao tiver pipes (else) ✅
 * TODO: arrumar: segundo heredoc do pipe nao escreve no arquivo, apenas cria ✅
 * TODO: arrumar o redirect quando o arquivo no existir ✅
 * TODO: "cat << e > a.txt | ls -l"   ✅
 * ⬆️ se der CTRL+C no heredoc deve cancelar tudo e nao esta cancelando
*/
