#include "../inc/libs.h"

void	set_shlvl(t_shell *data)
{
	t_var	*envvar;
	int		value;
	char	*str_value;

	envvar = find_envvar(data->envvar, "SHLVL");
	if (!envvar)
	{
		add_new_envvar(data->envvar, "SHLVL", "1", 0);
		add_new_envvar(data->envvar_export, "SHLVL", "1", 0);
		return ;
	}
	value = ft_atoi(envvar->value);
	if (value >= 999)
		set_envvar(data, "SHLVL", "1", 0);
	else
	{
		value++;
		str_value = ft_itoa(value);
		set_envvar(data, "SHLVL", str_value, 0);
		free(str_value);
	}
}

void	set_questionvar(t_shell *data)
{
	t_var	*envvar;
	char	*str_value;

	envvar = find_envvar(data->envvar, "?");
	if (!envvar)
	{
		add_new_envvar(data->envvar, "?", "0", 0);
		add_new_envvar(data->envvar_export, "?", "0", 0);
	}
	else
	{
		str_value = ft_itoa(data->return_status);
		set_envvar(data, "?", str_value, 0);
		free(str_value);
	}
}
