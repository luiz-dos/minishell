#include "../inc/libs.h"

void	mini_pwd(t_shell	*data)
{
	char	*pwd;
	t_var	*pwd_envvar;

	pwd_envvar = find_envvar(data->envvar, "PWD");
	if (pwd_envvar)
	{
		printf("%s\n", pwd_envvar->value);
		return ;
	}
	else if (!pwd_envvar)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror(pwd);
			return ;
		}
		printf("%s\n", pwd);
		free(pwd);
	}
}
