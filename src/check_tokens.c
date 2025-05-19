#include "../inc/libs.h"

int	check_tokens_two(t_tokens *token)
{
	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (token->type != PIPE && token->next->type >= PIPE)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", token->next->content);
		return (0);
	}
	if (token->type == PIPE && (!token->prev || (token->next && token->next->type == PIPE)))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_tokens(t_shell *data)
{
	t_tokens	*token;

	token = data->tokens;
	if (!token->next && ft_strcmp(token->content, ".") == 0)
	{
		printf("minishell: .: filename argument required\n");
		return (0);
	}
	while (token)
	{
		if (token->type >= PIPE && token->type <= REDIR_IN)
		{
			if (!check_tokens_two(token))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
