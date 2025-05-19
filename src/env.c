#include "../inc/libs.h"

void	mini_env(t_var *lst)
{
	t_var	*current;

	/* verificar se tem argumentos, se tiver, exibir messagem de erro */
	current  = lst;
	while (current)
	{
		if (current->env == true && current->value != NULL)
			printf("%s\n", current->content);
		current = current->next;
	}
}
