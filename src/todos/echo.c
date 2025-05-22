#include "../inc/libs.h"

void	mini_echo(char	**args, int fd)
{
	bool	flag_nl;
	int		i;

	if (!args)
		return ;
	flag_nl = false;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		flag_nl = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag_nl)
		ft_putchar_fd('\n', fd);
}
