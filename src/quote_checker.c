#include "../inc/libs.h"

static bool space_trim(char *input, char *temp)
{
	static int	x = 0;
	static int	z = 0;
	char		c;

	if (!input[x])
		return (false);
	while (input[x] && input[x] != '\'' \
	&& input[x] != '\"' && !ft_isspace(input[x]))
		temp[z++] = input[x++];
	if (input[x] == '\'' || input[x] == '\"')
	{
		c = input[x];
		temp[z++] = input[x++];
		while (input[x] && input[x] != c)
			temp[z++] = input[x++];
		temp[z++] = input[x++];
	}
	if (input[x] && ft_isspace(input[x]))
		temp[z++] = ' ';
	while (input[x] && ft_isspace(input[x]))
		x++;
	temp[z] = '\0';
	if (input[x] == '\0')
		return (z = 0, x = 0, true);
	return (false);
}

static char *trim_input(char *input)
{
	char *temp;
	
	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (space_trim(input, temp) == false)
		(void)0;
	return (temp);
}

static int input_cleaner(char *input)
{
	char *trim;

	if (!input)
		return (-1);
	trim = trim_input(input);
	if (!trim)
		return (-1);
	ft_strlcpy(input, trim, ft_strlen(trim) + 1);
	free(trim);
	return (0);
}

static int match_quotes(const char *input)
{
	char c;
	
	c = 0;
	while (*input != '\0')
	{
		if (*input == '"' || *input == '\'')
		{
			if (c == 0)
				c = *input;
			else if (c == *input)
				c = 0;
		}
		input++;
	}
	return (c);
}

bool ft_quote_checker(char *input)
{
	if(match_quotes(input))
	{
		printf("unmatched quotes (falta terminar!!!)\n");//todo; funcao propria pra lidar com errors
		return (false);
	}
	if (input_cleaner(input) == -1)
	{
		printf("Fail to allocat memory (falta terminar!!!)\n");//todo; funcao propria pra lidar com errors
		return (false);
	}
	// printf("%s\n", input);
	return (true);
}
