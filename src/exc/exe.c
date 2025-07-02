#include "../../inc/libs.h"

void	cleanup_bkp(int stdin_bkp, int stdout_bkp)
{
	if (stdin_bkp != -1)
	{
		dup2(stdin_bkp, STDIN_FILENO);
		close(stdin_bkp);
	}
	if (stdout_bkp != -1)
	{
		dup2(stdout_bkp, STDOUT_FILENO);
		close(stdout_bkp);
	}
}

void	exe(t_shell *data)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;
	int			stdin_bkp;
	int			stdout_bkp;
	
	cmd = data->commands;
	stdin_bkp = -1;
	stdout_bkp = -1;
	if (cmd->has_pipe)
		handle_pipeline(data, cmd);
	else
	{
		if (has_in_redir(cmd) || has_heredoc_redir(cmd) || has_out_redir(cmd))
		{
			stdin_bkp = dup(STDIN_FILENO);
			stdout_bkp = dup(STDOUT_FILENO);
			if (stdin_bkp == -1 || stdout_bkp == -1)
			{
				perror("dup failed");
				return ;
			}
		}
		if (handle_all_redirects(cmd) == -1)
		{
			cleanup_bkp(stdin_bkp, stdout_bkp);
			return ;
		}
		if (is_builtin(cmd->cmd))
			execute_builtin(data, cmd);
		else
		{
			set_sig_ignore();
			pid = create_fork();
			if (pid == 0)
			{
				set_sig_child();
				analize_ext_cmd(cmd->args);
			}
			else
			{
				cleanup_bkp(stdin_bkp, stdout_bkp);
				stdin_bkp = -1;
				stdout_bkp = -1;
				waitpid(pid, &status, 0);
				set_sig_main();
				if (WIFSIGNALED(status))
				{
					cleanup_bkp(stdin_bkp, stdout_bkp);
					printf("\n");
					set_questionvar(data, (128 + WTERMSIG(status)));
				}
				else
					set_questionvar(data, WEXITSTATUS(status));
			}
		}
	}
	cleanup_bkp(stdin_bkp, stdout_bkp);
}

/* TODO: lidar com os redirects quando nao tiver pipes (else) ✅
 * TODO: arrumar: segundo heredoc do pipe nao escreve no arquivo, apenas cria ✅
 * TODO: arrumar o redirect quando o arquivo no existir ✅
 * TODO: "cat << e > a.txt | ls -l"   ✅
 * ⬆️ se der CTRL+C no heredoc deve cancelar tudo e nao esta cancelando
*/
