#include "../inc/libs.h"

bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return(true);
	return(false);
}
