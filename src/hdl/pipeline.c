#include "../../inc/libs.h"

void	wait_for_children(t_shell *data, t_command *cmd, int cmd_count)
{
	int			i;
	int			status;
	pid_t		pid;
	t_command	*last_cmd;
	
	i = 0;
	status = 0;
	
	// Encontra o último comando para verificar seu status depois
	last_cmd = cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	
	// Espera por todos os filhos
	while (i < cmd_count)
	{
		pid = waitpid(-1, &status, 0);
		// Se for o último comando, salvar o status
		if (pid == last_cmd->pid)
		{
			if (WIFEXITED(status))
				set_questionvar(data, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				set_questionvar(data, (128 + WTERMSIG(status)));
		}
		i++;
	}
}

void	handle_pipeline(t_shell *data, t_command *cmd)
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	t_command	*current;
	int			cmd_count;
	
	prev_fd = -1;
	cmd_count = 0;
	current = cmd;
	while (current)
	{
		if (current->has_pipe)
			create_pipe(fd);
		pid = create_fork();
		if (pid == 0)
		{
			if (!current->has_heredoc && !current->infile && prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (!current->outfile && current->has_pipe)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (handle_redirects(current) == -1)
				exit(1);
			if (is_builtin(current->cmd))
				execute_builtin(data, current);
			else
				exec_external_cmd(current->args);
			exit(EXIT_SUCCESS);
		}
		current->pid = pid; // Armazena o PID para esperar depois
		cmd_count++;
		if (prev_fd != -1)
			close(prev_fd);
		if (current->has_pipe)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	// Espera por todos os processos filhos
	wait_for_children(data, cmd, cmd_count);
}
