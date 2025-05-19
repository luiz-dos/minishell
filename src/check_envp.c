#include "../inc/libs.h"

int	check_envp(char **envp)
{
	int	i;

	if (!envp || !*envp)
	{
		printf("-minishell: environment not found\n");
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
		{
			if (*(envp[i] + 5) != '\0')
				return (0);
			else
			{
				printf("-minishell: PATH variable is empty\n");
				return (1);
			}
		}
		i++;
	}
	printf("-minishell: PATH variable not found\n");
	return (1);
}
