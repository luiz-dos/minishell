/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:06:22 by gufreire          #+#    #+#             */
/*   Updated: 2025/05/22 20:40:15 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

int		redirects(char *str, char **input, int *i)
{
		if ((input[0][0] == '<' && input[0][1] == '<') || (input[0][0] == '>' && input[0][1] == '>'))
		{
			str[(*i)++] = '\2';
			str[(*i)++] = (**input);
			str[(*i)++] = (**input);
			str[(*i)++] = '\2';
			(*input) += 2;
			return (1);
		}
		else if (input[0][0] == '>' || input[0][0] == '<')
		{
			str[(*i)++] = '\2';
			str[(*i)++] = (**input);
			str[(*i)++] = '\2';
			(*input) += 1;
			return (1);
		}
		else if (input[0][0] == '|')
		{
			str[(*i)++] = '\3';
			(*input) += 1;
			return (1);
		}
		return (0);
}

char	*tokenization(char *str, char *input)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (*input)
	{
		if (quote == 0 && (*input == '\"' || *input == '\''))
			quote = *input;
		else if (quote == *input)
			quote = 0;
		if (quote == 0 && *input == ' ')
			*input = '\2';
		if (!(quote == 0 && redirects(str, &input, &i)))
			str[i++] = *input++;
	}
	return (str);
}

void	pars(char *input)
{
	char	*str;
	char	**pipes;
	int		i;
	
	
	str = (char *)ft_calloc(ft_strlen(input), 3);
	// if (!str)
	// 	return (NULL);
	str = tokenization(str, input);
	pipes = ft_split(str, '\3');
	i = 0;
	while (pipes && pipes[i])
	{
		
	}
}

