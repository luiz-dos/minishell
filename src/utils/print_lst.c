#include "../../inc/libs.h"

/* funcoes apenas para testes */

void	print_token_lst(t_tokens *lst)
{
	t_tokens	*current;
	int			i;
	const char	*type_names[] = { "CMD", "ARG", "FILENAME" ,"DELIM", "PIPE", 
		"HEREDOC", "APPEND_OUT", "REDIR_OUT","REDIR_IN"};
	current = lst;
	i = 1;
	while(current)
	{
		if (i == 1)
			printf("=================================\n");
		printf("Token %d (%s): %s\n", i, type_names[current->type], current->content);
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
	while (current)
	{
		redir = current->redirs;
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
				if (redir->type == HEREDOC)
					printf("Delimiter: %s\n", redir->filename);
				else
					printf("Filename: %s\n", redir->filename);
			}
			redir = redir->next;
		}
		if (current->has_pipe)
			printf("Pipe: True\n");
		printf("=================================\n");
		printf("\n");
		current = current->next;
	}
}
