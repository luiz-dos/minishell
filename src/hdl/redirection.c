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

int	handle_redirects(t_command *cmd)
{
	t_redir_out *out;

	if (cmd->infile && redirect_input(cmd->infile) == -1)
		return (-1);
	out = cmd->out_redirs;
	while (out)
	{
		if (out->append)
		{
			if (redirect_output_append(out->filename) == -1)
				return (-1);
		}
		else
		{
			if (redirect_output(out->filename) == -1)
				return (-1);
		}
		out = out->next;
	}
	if (cmd->has_heredoc)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	return (0);
}
