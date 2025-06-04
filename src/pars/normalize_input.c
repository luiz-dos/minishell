#include "../../inc/libs.h"

static bool	is_double_operator(const char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (true);
	if (input[i] == '<' && input[i + 1] == '<')
		return (true);
	return (false);
}

static void	handle_operator(char *input, int *i, int *j, char *new)
{
	if (*j > 0 && new[*j -1] != ' ')
	{
		new[*j] = ' ';
		(*j)++;
	}
	new[*j] = input[*i];
	(*i)++;
	(*j)++;
	if (is_double_operator(input, *i -1))
	{
		new[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
	if (input[*i] != '\0' && input[*i] != ' ')
	{
		new[*j] = ' ';
		(*j)++;
	}
}

static bool	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

void	update_quote(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == '\0')
			*quote = c;
		else if (*quote == c)
			*quote = '\0';
	}
}

static int extra_spaces(char *input)
{
    int     i;
    int     count;
    char    quote;

    i = 0;
    count = 0;
    quote = '\0';
    while (input[i])
    {
        update_quote(input[i], &quote);
        if (quote == '\0' && is_operator(input[i]))
        {
            if (i > 0 && input[i - 1] != ' ')
                count++;
            if (is_double_operator(input, i))
                i++;
            if (input[i + 1] && input[i + 1] != ' ')
                count++;
        }
        i++;
    }
    return (count);
}

char	*normalize_input(char *input)
{
	char	*new;
	int		i;
	int		j;
	char	quote;
	int		len;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	new = malloc(len + extra_spaces(input) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (input[i])
	{
		update_quote(input[i], &quote);
		if (quote == '\0' && is_operator(input[i]))
			handle_operator(input, &i, &j, new);
		else
			new[j++] = input[i++];
	}
	new[j] = '\0';
	return (new);
}
