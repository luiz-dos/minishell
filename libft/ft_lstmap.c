/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:44 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/04/23 15:31:50 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterates the list ’lst’ and applies the function ’f’ on the
content of each node. Creates a new list resulting of the
successive applications of the function ’f’.
The ’del’ function is used to delete the content of a node if needed.
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
del: The address of the function used to deletethe content
of a node if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*current;
	void	*new_content;

	if (lst && f && del)
	{
		new_list = NULL;
		new_content = NULL;
		current = lst;
		while (current)
		{
			new_content = f(current->content);
			new_node = ft_lstnew(new_content);
			if (!new_node)
			{
				ft_lstclear(&new_list, del);
				return (NULL);
			}
			ft_lstadd_back(&new_list, new_node);
			current = current->next;
		}
		return (new_list);
	}
	return (NULL);
}
