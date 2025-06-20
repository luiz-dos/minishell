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

int	handle_infiles(t_redir_in *in)
{
	int fd;

	while (in && in->next)
	{
		fd = open(in->filename, O_RDONLY, 0);
		if (fd == -1)
		{
			perror(in->filename);
			set_questionvar(shell(), 1);
			return (-1);
		}
		close(fd);
		in = in->next;
	}
	return (0);
}

int	handle_outfiles(t_redir_out *out)
{
	while (out)
	{
		if (out->append && redirect_output_append(out->filename) == -1)
			return (-1);
		else
		{
			if (redirect_output(out->filename) == -1)
				return (-1);
		}
		out = out->next;
	}
	return (0);
}

int	handle_redirects(t_command *cmd)
{
	t_redir_in	*in;
	t_redir_out	*out;

	in = cmd->in_redirs;
	if (in)
	{
		if (handle_infiles(in) == -1)
			return (-1);
		while (in && in->next)
			in = in->next;
		if (in && in->filename && redirect_input(in->filename) == -1)
			return (-1);
	}
	out = cmd->out_redirs;
	if (out && handle_outfiles(out) == -1)
		return (-1);
	if (cmd->has_heredoc)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	return (0);
}
