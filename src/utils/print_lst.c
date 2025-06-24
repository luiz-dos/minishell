#include "../../inc/libs.h"

/* funcoes apenas para testes */

void	print_token_lst(t_tokens *lst)
{
	t_tokens	*current;
	int			i;

	current = lst;
	i = 1;
	while(current)
	{
		if (i == 1)
			printf("=================================\n");
		printf("Token %d (type: %d): %s\n", i, current->type, current->content);
		i++;
		current = current->next;
	}
}

void	print_cmd_lst(t_command *lst)
{
	t_command	*current;
	t_redir		*redir;
	int			i;

	current = lst;
	redir = current->redirs;
	while (current)
	{
		printf("=================================\n");
		printf("Command name: %s\n", current->cmd);
		if (current->args)
		{
			printf("Args:");
			i = -1;
			while (current->args[++i])
				printf(" %s", current->args[i]);
			printf("\n");
		}
		if (current->infile)
			printf("Infile: %s\n", current->infile);
		while (redir)
		{
			if(redir->filename)
			{
				printf("Redir: %s\n", redir->filename);
				printf("Redir type: %d\n", redir->type);
			}
			redir = redir->next;
		}
		if (current->has_heredoc)
			printf("Heredoc: True \n");
		if (current->heredoc_delim)
			printf("Delim: %s\n", current->heredoc_delim);
		if (current->has_pipe)
			printf("Pipe: True\n");
		printf("=================================\n");
		printf("\n");
		current = current->next;
	}
}
