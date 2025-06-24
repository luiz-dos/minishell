#include "../../inc/libs.h"

/* < */
int 	redirect_input(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY, 0);
	if (fd_in == -1)
	{
		perror(file);
		set_questionvar(shell(), 1);
		return (-1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd_in);
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	return (0);
}

/* > */
int	redirect_output(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(file);
		set_questionvar(shell(), 1);
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd_out);
		exit(EXIT_FAILURE);
	}
	close(fd_out);
	return (0);
}

/* >> */
int	redirect_output_append(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror(file);
		set_questionvar(shell(), 1);
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd_out);
		exit(EXIT_FAILURE);
	}
	close (fd_out);
	return (0);
}

int	process_heredoc(t_command *cmd, t_redir *redir)
{
	int	last;

	if (!redir)
		return (0);
	last = -1;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (create_heredoc(cmd, redir) == -1)
				return (-1);
			if (last != -1)
				close(last);
			last = cmd->heredoc_fd;
		}
		redir = redir->next;
	}
	if (last != -1)
	{
		if (dup2(last, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			return (-1);
		}
		if (close(last) == -1)
			perror("close heredoc fd");
	}
	return (0);
}

int	handle_redirects(t_command *cmd)
{
	t_redir	*redir;

	if (!cmd || process_heredoc(cmd, cmd->redirs) == -1)
		return (-1);
	redir = cmd->redirs;
	while(redir)
	{
		if (redir->type == REDIR_IN && redirect_input(redir->filename) == -1)
			return (-1);
		if (redir->type == REDIR_OUT && redirect_output(redir->filename) == -1)
			return (-1);
		if (redir->type == APPEND_OUT && redirect_output_append(redir->filename) == -1)
			return (-1);
		redir = redir->next;
	}
	out = cmd->out_redirs;
	if (out && handle_outfiles(out) == -1)
		return (-1);
	return (0);
}
