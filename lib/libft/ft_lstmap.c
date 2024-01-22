/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:02:14 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/29 17:39:55 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;
	t_list	*next;

	if (!lst)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (NULL);
	curr = head;
	next = lst->next;
	while (next)
	{
		curr->next = ft_lstnew(f(next->content));
		if (!(curr->next))
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		curr = curr->next;
		next = next->next;
	}
	return (head);
}
