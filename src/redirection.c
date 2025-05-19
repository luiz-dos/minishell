#include "../inc/libs.h"

/* < */
int 	redirect_input(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY, 0);
	if (fd_in == -1)
	{
		perror(file);
		ft_start_shell()->return_status = 1;
		set_questionvar(ft_start_shell());
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
		ft_start_shell()->return_status = 1;
		set_questionvar(ft_start_shell());
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
		ft_start_shell()->return_status = 1;
		set_questionvar(ft_start_shell());
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
	if (cmd->infile)
	{
		if (redirect_input(cmd->infile) == -1)
			return (-1);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
		{
			if (redirect_output_append(cmd->outfile) == -1)
				return (-1);
		}
		else
		{
			if (redirect_output(cmd->outfile) == -1)
				return (-1);
		}
	}
	if (cmd->has_heredoc)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	return (0);
}
