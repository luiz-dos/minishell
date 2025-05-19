#include "../inc/libs.h"

t_var   *copy_var_node(t_var *envvar)
{
    t_var   *copy;

    copy = ft_calloc(1, sizeof(t_var));
    if (!copy)
        return (NULL);
    copy->content = ft_strdup(envvar->content);
    copy->name = ft_strdup(envvar->name);
    copy->value = ft_strdup(envvar->value);
    copy->env = envvar->env;
    copy->exp = envvar->exp;
    copy->next = NULL;
    copy->prev = NULL;
    return (copy);
}

t_var	*create_lst_export(t_shell *data)
{
	t_var	*current;
	t_var	*head;
	t_var	*node_export;

	current = data->envvar;
	head = NULL;
	while (current)
	{
		node_export = copy_var_node(current);
		if (!node_export)
		{
			free_lst(head);
			return (NULL);
		}
		add_var_back(&head, node_export);
		if (current->next == NULL)
			remove_envvar(&head, node_export);
		current = current->next;
	}
	return(head);
}

void	swap_nodes(t_var *current, t_var *next)
{
	char	*content_temp;
	char	*name_temp;
	char	*value_temp;

	content_temp = current->content;
	name_temp = current->name;
	value_temp = current->value;
	current->content = next->content;
	current->name = next->name;
	current->value = next->value;
	next->content = content_temp;
	next->name = name_temp;
	next->value = value_temp;
}

void	sort_var(t_var *lst)
{
	t_var	*current;
	int		swap;

	if (!lst)
		return ;
	swap = 1;
	while (swap)
	{
		swap = 0;
		current = lst;
		while (current && current->next)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap_nodes(current, current->next);
				swap = 1;
			}
			else
				current = current->next;
		}
	}
}

void	print_export(t_shell *data)
{
	t_var	*current;

	sort_var(data->envvar_export);
	current = data->envvar_export;
	while (current)
	{
		if (current->exp && current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else if (current->exp && !current->value)
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}
