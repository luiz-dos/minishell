#include "../../inc/libs.h"

void save_std_fileno(int code)
{
	t_shell *data;

	data = shell();
	if (code == 0)
	{
		if (data->std_fileno[0] != -1) // Fecha antigos descritores
			close(data->std_fileno[0]);
		if (data->std_fileno[1] != -1)
			close(data->std_fileno[1]);

		data->std_fileno[0] = dup(STDIN_FILENO);
		data->std_fileno[1] = dup(STDOUT_FILENO);
	}
	else if (code == 1 && data->std_fileno[0] != -1 && data->std_fileno[1] != -1)
	{
		dup2(data->std_fileno[0], STDIN_FILENO);
		dup2(data->std_fileno[1], STDOUT_FILENO);
		close(data->std_fileno[0]);
		close(data->std_fileno[1]);
		data->std_fileno[0] = -1;
		data->std_fileno[1] = -1;
	}
}

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
		if (there_in_redir(cmd) || there_out_redir(cmd))
		{
			stdin_bkp = dup(STDIN_FILENO);
			stdout_bkp = dup(STDOUT_FILENO);
			if (stdin_bkp == -1 || stdout_bkp == -1)
			{
				perror("dup failed");
				cleanup_bkp(stdin_bkp, stdout_bkp);
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
				waitpid(pid, &status, 0);
				set_sig_main();
				if (WIFSIGNALED(status) || WTERMSIG(status) == SIGINT)
				{
					cleanup_bkp(stdin_bkp, stdout_bkp);
					printf("\n");
					set_questionvar(data, 130);
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
 * TODO: "cat << e > a.txt | ls -l"   
 * ⬆️ se der CTRL+C no heredoc deve cancelar tudo e nao esta cancelando
*/
