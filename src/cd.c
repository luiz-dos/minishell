#include "../inc/libs.h"

char	*get_dir(char *arg, int *flag_free, t_shell *data)
{
	char	*dir;

	dir = NULL;
	if (ft_strcmp(arg, "-") == 0)
	{
		dir = get_value(data, "OLDPWD");
		if (only_space(dir))
		{
			printf("NO OLDPWD\n");
			return (NULL);
		}
	}
	else
	{
		dir = ft_strdup(arg);
		*flag_free = 1;
	}
	return (dir);
}

void	update_pwd(t_shell *data, char *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error using getcwd\n");
		return ;
	}
	if (ft_strcmp(dir, ".") == 0)
	{
		set_envvar(data, "OLDPWD", pwd, 1);
		free(pwd);
		return ;
	}
	oldpwd = get_value(data, "PWD");
	if (only_space(oldpwd))
		set_envvar(data, "OLDPWD", oldpwd, 1);
	set_envvar(data, "PWD", pwd, 0);
	free(pwd);
}

void	change_dir(char *dir, int flag_free, t_shell *data)
{
	struct stat buf;
	if (dir && dir[0] != 0 && chdir(dir) == -1)
	{
		if (stat(dir, &buf) == 0)
		{
			if ((buf.st_mode & __S_IFREG))
				perror(dir);
		}
		else
			perror(dir);
		data->return_status = 1;
		set_questionvar(data);
	}
	else
		update_pwd(data, dir);
	if (flag_free == 1)
		free(dir);
}

void    cd(t_shell *data, char **args)
{
	char	*dir;
	int		flag_free;

	dir = NULL;
	flag_free = 0;
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->return_status = 1;
		set_questionvar(data);
	}
	if (!args[1] || ft_strcmp(args[1], "--") == 0)
	{
		dir = get_value(data, "HOME");
		if (only_space(dir))
			printf("HOME not set\n");
	}
	else if (args[1])
		dir = get_dir(args[1], &flag_free, data);
	if (dir)
		change_dir(dir, flag_free, data);
}
