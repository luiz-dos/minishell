/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:40 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:26:39 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

t_tokens	*ft_tokenlast(t_tokens *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*curr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_tokenlast(*lst);
	curr->next = new;
	new->prev = curr;
}

void	init_tokens(char **tokens)
{
	t_tokens	*node;
	t_tokens	*head;
	int			i;

	head = NULL;
	i = 0;
	while (tokens[i])
	{
		node = ft_calloc(1, sizeof(t_tokens));
		node->content = ft_strdup(tokens[i]);
		node->type = -1;
		node->single_quotes = false;
		node->double_quotes = false;
		ft_tokenadd_back(&head, node);
		i++;
	}
	shell()->tokens = head;
	free_array(tokens);
}

void	create_tokens(char **tokens)
{
	t_tokens	*temp;

	init_tokens(tokens);
	temp = shell()->tokens;
	while (temp)
	{
		temp->content = del_nquotes(temp->content);
		temp = temp->next;
	}
	set_token_type(shell()->tokens);
}
