#include "../../inc/libs.h"

void	write_line_to_pipe(char *line, int fd[2])
{
	expand_dolar(&line);
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void	loop_heredoc(t_redir *redir, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (global_sig == SIGINT)
		{
			if (line)
				free(line);
			close(fd[1]);
			free_exit(shell(), 130);
		}
		if (!line) // EOF (CTRL+D)
		{
			write(STDERR_FILENO, WARNING_EOF, 60);
			break;
		}
		if (ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break;
		}
		write_line_to_pipe(line, fd);
	}
}

void	child_heredoc(t_redir *redir, int fd[2])
{
	set_sig_heredoc();
	close(fd[0]);
	loop_heredoc(redir, fd);
	close(fd[1]);
	free_exit(shell(), 0);
}

int	create_heredoc(t_command *current, t_redir *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	
	create_pipe(fd);
	set_sig_ignore();
	pid = create_fork();
	if (pid == 0)
		child_heredoc(redir, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		set_sig_main();
		if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
		{
			close_fds(fd);
			current->heredoc_fd = -1;
			set_questionvar(shell(), 130);
			return (-1);
		}
		current->heredoc_fd = fd[0];
	}
	return (0);
}
