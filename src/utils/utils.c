#include "../../inc/libs.h"

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

int count_args(char **args)
{
    int i;

    if (!args || !*args)
        return (0);
    i = 0;
    while (args[i])
        i++;
    return (i);
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

	data = shell();
	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_exit(data, EXIT_FAILURE);
	}
}

pid_t    create_fork(void)
{
	pid_t   pid;
	t_shell *data;

	pid = fork();
	data = shell();
	if (pid == -1)
	{
		perror("fork");
		free_exit(data, EXIT_FAILURE);
	}
	return (pid);
}
