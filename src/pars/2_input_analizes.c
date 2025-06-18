#include "../../inc/libs.h"

int mark_quotes(char *input, int *i)
{
	char quote;

	quote = input[(*i)];
	input[(*i)] *= -1;
	while (input[++(*i)])
	{
		if (input[(*i)] == quote)
		{
			input[(*i)] *= -1;
			return ((*i));
		}
	}
	return ((*i));
}

void	mark_input(char	*input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = mark_quotes(input, &i);
		if (input[i] == ' ')
			input[i] = N_SPACE;
		i++;
	}
}

void	init_tokens(char **tokens)
{
	t_tokens	*node;
	t_tokens	*head;
	int			i;

	head = NULL;
	i = 0;
	while (tokens[i])
	{
		node = ft_calloc(1, sizeof(t_tokens));
		node->content = ft_strdup(tokens[i]);
		node->type = -1;
		node->single_quotes = false;
		node->double_quotes = false;
		ft_tokenadd_back(&head, node);
		i++;
	}
	shell()->tokens = head;
	free_array(tokens);
}

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
	bool	end;

	i = -1;
	end = false;
	while(!end && (*input)[++i])
	{
		if ((*input)[i] == '$' && inside_quotes((*input), i) != 1
			&& (*input)[i + 1] != '\0')
		{
			if (handle_expansion(input, shell(), i) == 1)
				i = 0;
			if ((*input)[i] == '\0')
				end = true;
		}
	}
}

int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == N_DQUOTE || str[i] == N_SQUOTE)
			count++;
	}
	return (count);
}

char	*del_quotes(char *str)
{
	char	*new;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(str);
	new = (char *)malloc((len - count_quotes(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != N_DQUOTE && str[i] != N_SQUOTE)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void	create_tokens(char **tokens)
{
	t_tokens *temp;

	init_tokens(tokens);
	temp = shell()->tokens;
	while (temp)
	{
		temp->content = del_quotes(temp->content);
		ft_set_token_type(temp);
		temp = temp->next;
	}
}

void	input_analizes(t_shell *data)
{
	char	**tokens;
	char	*normalized;

	if (ft_quote_checker(data->input))  
	{
		expand_dolar(&data->input);
		normalized = normalize_input(data->input);
		if (!normalized)
			return ;
		free(data->input);
		data->input = normalized;
		// printf("---Expanded: %s\n", shell()->input); /* somente para testes */
		mark_input(data->input);
		// printf("-----Marked: %s\n", shell()->input); /* somente para testes */
		tokens = ft_split(data->input, N_SPACE);
		if (!tokens)
		{
			free_exit(data);
			exit (1);
		}
		create_tokens(tokens);
		// print_token_lst(data->tokens); /* somente para testes */
		if (check_tokens(data))
		{
			data->commands = create_cmd_list(data->tokens);
			// print_cmd_lst(data->commands); /* somente para testes */
			exe(data);
		}
	}
}
