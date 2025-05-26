#include "../../inc/libs.h"

void execute_commands(t_shell *data)
{
	t_command *cmd;
	pid_t pid;
	int status;

	cmd = data->commands;
	while (cmd != NULL)
	{
		if (cmd->has_heredoc)
			create_heredoc(cmd); // Cria o heredoc se o comando precisar
		if (ft_strcmp(cmd->cmd, "exit") == 0)
		{
			execute_builtin(data, cmd); // Executa exit diretamente no pai
			return; // Sai de execute_commands (encerra o Minishell)
		}
		ft_ignore_some_signals();
		pid = create_fork();
		if (pid == 0)
		{
			ft_redefine_child_signals();
			handle_redirects(cmd); // Lida com redirecionamentos (incluindo heredoc)
			if (is_builtin(cmd->cmd))
				execute_builtin(data, cmd);
			else
				exec_external_cmd(cmd->args);
			ft_config_signals(0);
			exit(data->return_status); // Sai com o status do comando
		}
		else
		{
			waitpid(pid, &status, 0);
			data->return_status = WEXITSTATUS(status);
			set_questionvar(data);
		}
		cmd = cmd->next;
	}
}
