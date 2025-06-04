#include "../../inc/libs.h"

static int	check_dolar(t_shell *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->input[i] == ' ')
		i++;
	if (data->input[i] == '$')
	{
		temp = ft_strdup(data->input);
		// printf("temp: %s\n", temp);
		free(data->input);
		data->input = expand_envvar(data, temp);
		// printf("data->input: %s\n", data->input);
		free(temp);
		if (only_space(data->input))
			return (0);
	}
	return (1);
}

void	ft_input_analizes(t_shell *data)
{
	char	*normalized;

	normalized = normalize_input(data->input);
	if (!normalized)
		return ;
	free(data->input);
	data->input = normalized;
	printf("-Normalized: %s\n", shell()->input); /* somente para testes */
	if (ft_quote_checker(data->input) && check_dolar(data))  
	{
		ft_tokenization(data);
		strip_quotes_all(data->tokens);
		expand_envvar_all(data);
		ft_set_token_type(data->tokens);
		print_token_lst(data->tokens); /* somente para testes */
		if (check_tokens(data))
		{
			data->commands = create_cmd_list(data->tokens);
			print_cmd_lst(data->commands); /* somente para testes */
			exe(data);
		}
	}
}
