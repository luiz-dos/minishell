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
	t_redir_out	*outs;
	t_redir_in	*in;
	int			i;

	current = lst;
	outs = current->out_redirs;
	in = current->in_redirs;
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
		while (in)
		{
			if(in->filename)
				printf("Infile ( < ): %s\n", in->filename);
			if (in->heredoc_delim)
				printf("Heredoc_delim: %s\n", in->heredoc_delim);
			in = in->next;
		}
		while (outs && outs->filename)
		{
			if(outs->append == 0)
				printf("Outfile (substituir > ): %s\n", outs->filename);
			else
				printf("Outfile (adicionar >> ): %s\n", outs->filename);
			outs = outs->next;
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
