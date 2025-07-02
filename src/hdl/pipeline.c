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

int	create_hd_in_pipeline(t_command *cmd)
{
	t_redir *redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC && create_heredoc(cmd, redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

void	child_pipeline(t_command *cmd, int fd[2], int prev_fd)
{
	// Redireciona entrada (se houver pipe anterior)
	if (!has_heredoc_redir(cmd) && !has_in_redir(cmd) && prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	// Redireciona saida (pipe ou arquivo)
	if (cmd->has_pipe && !has_out_redir(cmd))
		dup2(fd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	close_fds(fd);
	if (handle_redir_in_pipeline(cmd) == -1)
		free_exit(shell(), 1);
	if (is_builtin(cmd->cmd))
		execute_builtin(shell(), cmd);
	else
		analize_ext_cmd(cmd->args);
	exit(shell()->return_status);
}

int		process_hd_pipeline(t_command *cmd)
{
	t_command	*temp;

	temp = cmd;
	while(temp)
	{
		if (has_heredoc_redir(temp) && create_hd_in_pipeline(temp) == -1)
		{
			cleanup_hd_in_pipeline(cmd);
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}

void	handle_pipeline(t_shell *data, t_command *cmd)
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	int			cmd_count;
	
	if (process_hd_pipeline(cmd) == -1)
		return ;
	prev_fd = -1;
	cmd_count = 0;
	while (cmd)
	{
		if (cmd->has_pipe)
			create_pipe(fd);
		pid = create_fork();
		if (pid == 0)
			child_pipeline(cmd, fd, prev_fd);

		cmd->pid = pid;
		cmd_count++;
		update_pipe_descriptors(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	wait_for_children(data, data->commands, cmd_count);
}
