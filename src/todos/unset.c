#include "../inc/libs.h"

bool	check_options(char *option)
{
	if (option[0] == '-')
	{
	   printf("-minishell: %s : invalid option\n", option);
	   return (true);
	}
	return (false);
}

void	remove_envvar(t_var **lst, t_var *envvar)
{
	t_var	*temp;

	temp = find_envvar(*lst, envvar->name);
	if (!temp)
		return ;
	if (temp == envvar)
	{
		if (!temp->prev)
			*lst = envvar->next;
		else
			envvar->prev->next = envvar->next;
		free(envvar->content);
		free(envvar->name);
		free(envvar->value);
		free(envvar);
		return ;
	}
}

void	unset(t_shell *data, char **args)
{
	t_var	*envvar;
	int		i;

	if (!args || !*args || !args[1])
		return ;
	if (check_options(args[1]))
		return ;
	i = 1;
	while (args[i])
	{
		envvar = find_envvar(data->envvar, args[i]);
		if (envvar && ft_strcmp(envvar->name, "_") != 0)
		{
			remove_envvar(&data->envvar, envvar);
			envvar = find_envvar(data->envvar_export, args[i]);
			remove_envvar(&data->envvar_export, envvar);
		}
		i++;
	}
}
