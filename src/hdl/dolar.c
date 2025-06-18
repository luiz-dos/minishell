#include "../../inc/libs.h"

char	*insert_into_str(char *str, int i, char *value, char *name)
{
	char	*start;
	char	*temp;
	char	*new;

	start = ft_substr(str, 0, i);
	temp = ft_strjoin(start, value);
	new = ft_strjoin(temp, str + i + ft_strlen(name) + 1);
	free(start);
	free(temp);
	free(str);
	free(name);
	return (new);
}

bool	is_sep(char sep)
{
	if (sep == ' ' || sep == '\0' || sep == '"' || sep == '\''
		|| sep == '=' || sep == '/' || sep == '|' || sep == '&')
		return (true);
	return (false);
}

char	*get_var_name(char *input, int index)
{
	char	*var_name;
	int		start;
	int		len;

	start = index;
	len = 0;
	if (is_sep(input[start]))
		return (NULL);
	if (input[start] == '?')
	{
		index += 2;
		return (ft_strdup("?"));
	}
	while (ft_isalnum(input[start + len]) || input[start + len] == '_')
		len++;
	var_name = ft_strndup(input + start, len);
	if (!var_name)
		return (NULL);
	index += len + 1;
	return (var_name);
}

int	handle_expansion(char **input, t_shell *data, int i)
{
	char	*var_name;
	char	*var_value;
	t_var	*var;
	bool	free_flag;
	int		end;

	end = 0;
	var_name = get_var_name((*input), i + 1);
	if (!var_name)
		return (0);
	var = find_envvar(data->envvar, var_name);
	free_flag = false;
	var_value = "";
	if (var && var->value)
	{
		var_value = ft_strdup(var->value);
		free_flag = true;
	}
	(*input) = insert_into_str((*input), i, var_value, var_name);
	if (var_value[0] == 0)
		end = 1;
	if (free_flag)
		free(var_value);
	return(end);
}

void	expand_dolar(char **input)
{
	int		i;

	i = -1;
	while((*input)[++i])
	{
		if ((*input)[i] == '$' && inside_quotes((*input), i) != 1
			&& (*input)[i + 1] != '\0')
		{
			if (handle_expansion(input, shell(), i) == 1)
				i = -1;
		}
	}
}
