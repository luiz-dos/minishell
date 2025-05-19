#include "../inc/libs.h"

char	*extract_var_name(char *input, int *index)
{
	char	*var_name;
	int		start;
	int		len;

	start = *index + 1;
	len = 0;
	if (input[start] == '?')
	{
		*index += 2;
		return (ft_strdup("?"));
	}
	while (ft_isalnum(input[start + len]) || input[start + len] == '_')
		len++;
	var_name = ft_strndup(input + start, len);
	if (!var_name)
		return (NULL);
	*index += len + 1;
	return (var_name);
}

void	expand_envvar_two(char *expanded, char *var_name, char *var_value, int *j)
{
	free(var_name);
	ft_strcpy(expanded + *j, var_value);
	*j += ft_strlen(var_value);
}

char	*expand_envvar(t_shell *data, char *input)
{
	char	*expanded;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;

	expanded = (char *)malloc(1024);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && ft_inside_quotes(input, i) != 1)
		{
			var_name = extract_var_name(input, &i);
			var_value = get_value(data, var_name);
			expand_envvar_two(expanded, var_name, var_value, &j);
		}
		else
			expanded[j++] = input[i++];
	}
	expanded[j] = '\0';
	free(input);
	return (expanded); 
}
