#include "../../inc/libs.h"

void	wait_for_children(t_shell *data, t_command *cmd, int cmd_count)
{
	int			i;
	int			status;
	pid_t		pid;
	t_command	*last_cmd;
	
	i = 0;
	status = 0;
	last_cmd = cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (i < cmd_count)
	{
		pid = waitpid(-1, &status, 0);
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

void	update_pipe_descriptors(int *prev_fd, int fd[2], t_command *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->has_pipe)
		*prev_fd = fd[0];
	else
		*prev_fd = -1;
	close(fd[1]);
}

int	there_in_redir(t_command *cmd)
{
	t_redir	*curr;

	if (!cmd->redirs)
		return (0);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	there_out_redir(t_command *cmd)
{
	t_redir	*curr;

	if (!cmd->redirs)
		return (0);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == REDIR_OUT || curr->type == APPEND_OUT)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	child_process(t_command *cmd, int fd[2], int prev_fd)
{
	// Redireciona entrada (se houver pipe anterior)
	if (!cmd->has_heredoc && !there_in_redir(cmd) && prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	// Redireciona saida (pipe ou arquivo)
	if (cmd->has_pipe && !there_out_redir(cmd))
		dup2(fd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	close(fd[0]);
	close(fd[1]);
	if (handle_redirects(cmd) == -1)
		exit(1);
	if (is_builtin(cmd->cmd))
		execute_builtin(shell(), cmd);
	else
		analize_ext_cmd(cmd->args);
	exit(shell()->return_status);
}

void	handle_pipeline(t_shell *data, t_command *cmd)
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	int			cmd_count;

	prev_fd = -1;
	cmd_count = 0;
	while (cmd)
	{
		if (cmd->has_pipe)
			create_pipe(fd);
		pid = create_fork();
		if (pid == 0)
			child_process(cmd, fd, prev_fd);

		cmd->pid = pid;
		cmd_count++;
		update_pipe_descriptors(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	wait_for_children(data, data->commands, cmd_count);
}
