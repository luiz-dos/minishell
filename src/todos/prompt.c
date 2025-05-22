#include "../inc/libs.h"

char	*get_pathname(void)
{
	char	*pwd;
	char	*result;
	int		i;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_strdup("minishell$ "));
	i = 0;
	while (pwd[i])
		i++;
	while (i > 0 && pwd[--i] != '/')
		(void)pwd;
	if (i > 0)
		pwd[--i] = '~';
	result = ft_strjoin_free(ft_strdup(pwd + i), "$ ");
	free(pwd);
	return (result);
}

char	*color_to_prompt(char *prompt)
{
	char	*colored;
	size_t	size;

	size = ft_strlen(CYAN) + ft_strlen(RESET) + ft_strlen(prompt) + 1;
	colored = malloc(size);
	if (!colored)
		return (NULL);
	ft_strcpy(colored, CYAN);
	ft_strcat(colored, prompt);
	ft_strcat(colored, RESET);
	free(prompt);
	return (colored);
}
