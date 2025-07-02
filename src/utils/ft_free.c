#include "../../inc/libs.h"

void	free_lst(t_var *lst)
{
	t_var   *temp;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst->next;
		free(lst->content);
		free(lst->name);
		free(lst->value);
		free(lst);
		lst = temp;
	}
}

void	ft_tokenclear(t_tokens *lst)
{
	t_tokens	*tokens;
	t_tokens	*next;

	if (!lst)
		return ;
	tokens = lst;
	while (tokens != NULL)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

void	clean_redir(t_command *cmd)
{
	t_redir *next;
	t_redir	*lst;

	if (!cmd || !cmd->redirs) 
		return;
	lst = cmd->redirs;		
	while (lst)
	{
		next = lst->next;
		if (lst->filename)
			free(lst->filename);
		free(lst);
		lst = next;
	}
	cmd->redirs = NULL;
}

void	clean_cmd_list(t_command *lst)
{
	t_command	*temp;
	int			i;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		clean_redir(temp);
		if (temp->cmd)
			free(temp->cmd);
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		free(temp);
	}
}

// TODO: melhorar essa funcao
void	free_exit(t_shell *data, int exit_code)
{
	free_lst(data->envvar);
	free_lst(data->envvar_export);
	ft_tokenclear(data->tokens);
	clean_cmd_list(data->commands);
	if (data->input)
		free(data->input);
	if (data->ev_array)
		free_array(data->ev_array);
	close_remaining_fds();
	if (exit_code != -1)
		exit(exit_code);
}
