#include "../inc/libs.h"

int	only_space(char *str)
{
	int i;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	open_file(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		printf("Error opening %s", file);
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	close_fds(int fd[2])
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

void    create_pipe(int fd[2])
{
	t_shell *data;

	data = ft_start_shell();
	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_exit(data);
		exit(EXIT_FAILURE);
	}
}

pid_t    create_fork(void)
{
	pid_t   pid;
	t_shell *data;

	pid = fork();
	data = ft_start_shell();
	if (pid == -1)
	{
		perror("fork");
		free_exit(data);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
