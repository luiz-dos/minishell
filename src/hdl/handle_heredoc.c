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

void	handle_child_heredoc(t_command *current, int fd[2])
{
	close(fd[0]);
	loop_heredoc(current, fd);
	close(fd[1]);
	exit(0);
}
/* nao usada atualmente */
void	handle_parent_heredoc(t_command *current, int fd[2], pid_t pid)
{
	int	status;

	close(fd[1]); // fechar a escrita
	current->heredoc_fd = fd[0]; // salvar para caso precise dps
	current->heredoc_pid = pid;
	waitpid(pid, &status, 0);
}

void	create_heredoc(t_command *current)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	
	ft_ignore_some_signals();
	create_pipe(fd);
	pid = create_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // Configura sinais para heredoc
		close(fd[0]); // Fecha a leitura no filho
		handle_child_heredoc(current, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]); // Fecha a escrita no pai
		current->heredoc_fd = fd[0];
		current->heredoc_pid = pid;
		waitpid(pid, &status, 0);
		// Verifica se o filho terminou por um sinal (CTRL+C)
		if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		{
			close(fd[0]); // Fecha o descritor do pai
			current->heredoc_fd = -1; // Marca como inválido
			shell()->return_status = 130;
			current->has_heredoc = false; // Desativa o heredoc
		}
		ft_config_signals(0); // Volta para os sinais normais
	}
}
