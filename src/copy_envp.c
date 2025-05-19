#include "../inc/libs.h"

void	add_var_back(t_var **lst, t_var *node)
{
	t_var	*current;

	if (node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
}

t_var	*create_lst_envvar(char **envp)
{
	char	**current;
	t_var	*node;
	t_var	*head;

	head = NULL;
	current = envp;
	while (*current)
	{
		node = ft_calloc(1, sizeof(t_var));
		node->content = ft_strdup(*current);
		node->name = ft_strdup_two(*current, '=');
		node->value = ft_strdup(ft_strchr(*current, '=') + 1);
		node->env = true;
		node->exp = true;
		add_var_back(&head, node);
		current++;
	}
	return (head);
}
