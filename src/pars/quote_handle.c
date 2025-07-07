/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:38 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:26:31 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

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

int	mark_quotes(char *input, int *i)
{
	char	quote;

	quote = input[(*i)];
	input[(*i)] *= -1;
	while (input[++(*i)])
	{
		if (input[(*i)] == quote)
		{
			input[(*i)] *= -1;
			return ((*i));
		}
	}
	return ((*i));
}

void	mark_input(char	*input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = mark_quotes(input, &i);
		if (input[i] == ' ')
			input[i] = N_SPACE;
		i++;
	}
}

int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == N_DQUOTE || str[i] == N_SQUOTE)
			count++;
	}
	return (count);
}

char	*del_nquotes(char *str)
{
	char	*new;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(str);
	new = (char *)malloc((len - count_quotes(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != N_DQUOTE && str[i] != N_SQUOTE)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}
