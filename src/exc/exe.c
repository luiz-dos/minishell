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

void	exe(t_shell *data)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;
	
	cmd = data->commands;
	// Primeiro, processa todos os heredocs antes de executar os comandos
	while (cmd)
	{
		if (cmd->has_heredoc)
			create_heredoc(cmd);
		cmd = cmd->next;
	}
	cmd = data->commands;
	if (cmd->has_pipe)
		handle_pipeline(data, cmd);
	else
	{
		save_std_fileno(0);
		if (handle_redirects(cmd) == -1)
		{
			save_std_fileno(1);
			return ;
		}
		if (is_builtin(cmd->cmd))
			execute_builtin(data, cmd);
		else
		{
			pid = create_fork();
			if (pid == 0)
				exec_external_cmd(cmd->args);
			else
			{
				waitpid(pid, &status, 0);
				data->return_status = WEXITSTATUS(status);
				set_questionvar(data);
			}
		}
	}
	save_std_fileno(1);
}

/* TODO: lidar com os redirects quando nao tiver pipes (else) ✅
 * TODO: arrumar: segundo heredoc do pipe nao escreve no arquivo, apenas cria ✅
 * TODO: arrumar o redirect quando o arquivo no existir ✅
 * TODO: "cat << e > a.txt | ls -l"   
 * ⬆️ se der CTRL+C no heredoc deve cancelar tudo e nao esta cancelando
*/
