#include "../../inc/libs.h"

void	close_remaining_fds()
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_str(char *var_name, char *var_value)
{
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}
