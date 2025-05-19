/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:44:29 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/22 10:44:31 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the last node of the list.
lst: The beginning of the list.
Return: Last node of the list*/
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst)
	{
		current = lst;
		while (current->next != NULL)
			current = current->next;
		return (current);
	}
	return (NULL);
}
