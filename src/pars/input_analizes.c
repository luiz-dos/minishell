#include "../../inc/libs.h"

void	ft_input_analizes(t_shell *data)
{
	if (ft_quote_checker(data->input))  
	{
		ft_tokenization(data);
		strip_quotes_all(data->tokens);
		expand_envvar_all(data);
		ft_set_token_type(data->tokens);
		if (check_tokens(data))
		{
			data->commands = create_cmd_list(data->tokens);
			exe(data);
		}
		/* somente para testes */
		print_token_lst(data->tokens);
		print_cmd_lst(data->commands);
	}
}
