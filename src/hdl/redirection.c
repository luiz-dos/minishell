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
	t_redir	*redir;

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
	return (0);
}

int	process_last_redir(t_command *cmd, t_redir *in, t_redir *out)
{
	if (in)
	{
		if (in->type == REDIR_IN && redirect_input(in->filename) == -1)
			return (-1);
		else if (in->type == HEREDOC)
		{
			if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc");
				close(cmd->heredoc_fd);
				return (-1);
			}
			if (cmd->heredoc_fd != -1)
				close(cmd->heredoc_fd);
		}
	}
	if (out)
	{
		if (out->type == REDIR_OUT && redirect_output(out->filename) == -1)
			return (-1);
		else if (out->type == APPEND_OUT && redirect_output_append(out->filename) == -1)
			return (-1);
	}
	return (0);
}

int	handle_all_redirects(t_command *cmd)
{
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;

	last_in = NULL;
	last_out = NULL;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC && create_heredoc(cmd, redir) == -1)
			return (-1);
		redir = redir->next;
	}
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			last_in = redir;
		if (redir->type == REDIR_OUT || redir->type == APPEND_OUT)
			last_out = redir;
		redir = redir->next;
	}
	return (process_last_redir(cmd, last_in, last_out));
}
