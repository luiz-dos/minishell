#include "../../inc/libs.h"

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

void	update_heredoc_fd(t_command *cmd, int *fd_in)
{
	if (*fd_in != -1)
		close (*fd_in);
	*fd_in = cmd->heredoc_fd;
}

void	cleanup_hd_in_pipeline(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->heredoc_fd != -1)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		cmd = cmd->next;
	}
}

int	handle_redir_in_pipeline(t_command *cmd)
{
	t_redir	*redir;
	int		fd_in;
	int		fd_out;
	int		temp_fd;

	redir = cmd->redirs;
	fd_in = -1;
	fd_out = -1;
	while (redir)
	{
		if (redir->type >= APPEND_OUT && redir->type <= REDIR_IN)
		{
			temp_fd = open_redir_file(redir);
			if (temp_fd == -1)
				return (-1);
			update_fd_values(redir, &fd_in, &fd_out, temp_fd);
		}
		else if (redir->type == HEREDOC)
			update_heredoc_fd(cmd, &fd_in);
		redir = redir->next;
	}
	return (apply_last_redirs(fd_in, fd_out));
}
