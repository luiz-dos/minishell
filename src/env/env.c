#include "../../inc/libs.h"

void	mini_env(t_var *lst)
{
	t_var	*current;

	if (count_args(shell()->commands->args) > 1)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(shell()->commands->args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		set_questionvar(shell(), 127);
		return ;
	}
	current  = lst;
	while (current)
	{
		if (current->env == true && current->value != NULL)
			printf("%s\n", current->content);
		current = current->next;
	}
}
