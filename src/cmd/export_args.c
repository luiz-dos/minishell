#include "../../inc/libs.h"

void	check_value(t_command *cmd, char **var_name, char **var_value, int i)
{
	if (ft_strchr(cmd->args[i], '=') == NULL)
	{
		*var_name = ft_strdup(cmd->args[i]);
		*var_value = NULL;
	}
	else
	{
		*var_name = ft_strdup_two(cmd->args[i], '=');
		*var_value = ft_strdup(ft_strchr(cmd->args[i], '=') + 1);
	}
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	not_valid(t_command *cmd, int i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->args[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell()->return_status = 1;
	set_questionvar(shell());
}

void	mini_export(t_command *cmd)
{
	int		i;
	char	*var_name;
	char	*var_value;

	if (count_args(cmd->args) == 1)
		print_export(shell());
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			var_name = NULL;
			var_value = NULL;
			check_value(cmd, &var_name, &var_value, i);
			if (!is_valid_identifier(var_name))
				not_valid(cmd, i);
			else
				set_envvar(shell(), var_name, var_value, 1);
			if (var_name)
				free(var_name);
			if (var_value)
				free(var_value);
			i++;
		}
	}
}

