#include "../../inc/libs.h"

void	write_line_to_pipe(char *line, int fd[2])
{
	expand_dolar(&line);
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void	loop_heredoc(t_command *current, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (global_sig == SIGINT)
		{
			if (line)
				free(line);
			exit(130);
		}
		if (!line) // EOF (CTRL+D)
		{
			write(STDERR_FILENO, "-minishell: Warning: here-document delimited by end-of-file\n", 60);
			break;
		}
		if (ft_strcmp(line, current->heredoc_delim) == 0)
		{
			free(line);
			break;
		}
		write_line_to_pipe(line, fd);
	}
}

int	create_heredoc(t_command *current)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	
	create_pipe(fd);
	ft_ignore_some_signals();
	pid = create_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // Configura sinais para heredoc
		close(fd[0]);
		loop_heredoc(current, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]); // Fecha a escrita no pai
		waitpid(pid, &status, 0);
		ft_config_signals(0); // Volta para os sinais normais
		// Verifica se o filho terminou por um sinal (CTRL+C)
		if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		{
			close(fd[0]); // Fecha o descritor do pai
			current->heredoc_fd = -1; // Marca como inválido
			shell()->return_status = 130;
			return (-1);
		}
		current->heredoc_fd = fd[0];
	}
	return (0);
}
