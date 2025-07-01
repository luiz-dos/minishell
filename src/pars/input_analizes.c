#include "../../inc/libs.h"

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
		// printf("-Expa_Norma: %s\n", shell()->input); /* somente para testes */
		mark_input(data->input);
		// printf("-----Marked: %s\n", shell()->input); /* somente para testes */
		tokens = ft_split(data->input, N_SPACE);
		if (!tokens)
			free_exit(data, EXIT_FAILURE);
		create_tokens(tokens);
		// print_token_lst(data->tokens); /* somente para testes */
		if (check_tokens(data))
		{
			data->commands = create_cmd_list(data->tokens);
			// print_cmd_lst(data->commands); /* somente para testes */
			if (data->commands)
				exe(data);
		}
	}
}
