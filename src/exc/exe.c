#include "../../inc/libs.h"

void	save_std_fileno(void)
{
	static int	saved_stdin = -1;
	static int	saved_stdout = -1;

	if (saved_stdin != -1)
	{
		close(saved_stdin);
		saved_stdin = -1;
	}
	if (saved_stdout != -1)
	{
		close(saved_stdout);
		saved_stdout = -1;
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	shell()->std_fileno[0] = saved_stdin;
	shell()->std_fileno[1] = saved_stdout;
}

void	restore_std_fileno(void)
{
	if (shell()->std_fileno[0] != -1)
	{
		dup2(shell()->std_fileno[0], STDIN_FILENO);
		close(shell()->std_fileno[0]);
		shell()->std_fileno[0] = -1;
	}
	if (shell()->std_fileno[1] != -1)
	{
		dup2(shell()->std_fileno[1], STDOUT_FILENO);
		close(shell()->std_fileno[1]);
		shell()->std_fileno[1] = -1;
	}
}

void	exe(t_shell *data)
{
	t_command	*cmd;
	int			status;
	int			last_status;
	int			pid;

	cmd = data->commands;
	if (!cmd)
		return ;
	save_std_fileno();
	last_status = 0;
	while (cmd)
	{
		if (handle_redirects(cmd) == 1)
		{
			restore_std_fileno();
			return ;
		}
		if (is_builtin(cmd->cmd))
			execute_builtin(data, cmd);
		else
		{
			pid = create_fork();
			if (pid == 0)
				analize_ext_cmd(cmd->args);
			else
			{
				waitpid(pid, &status, 0);
				set_questionvar(data, WEXITSTATUS(status));
			}
		}
		cmd = cmd->next;
	}
	save_std_fileno();
}

/* TODO: lidar com os redirects quando nao tiver pipes (else) ✅
 * TODO: arrumar: segundo heredoc do pipe nao escreve no arquivo, apenas cria ✅
 * TODO: arrumar o redirect quando o arquivo no existir ✅
 * TODO: "cat << e > a.txt | ls -l"   
 * ⬆️ se der CTRL+C no heredoc deve cancelar tudo e nao esta cancelando
*/
