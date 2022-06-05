/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:48:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/01/07 10:56:09 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*first;

	list = (t_list *)malloc(sizeof(t_list *) * 1);
	first = list;
	while (lst)
	{
		if (!list)
		{
			while (first)
			{
				ft_lstdelone(first, del);
				first = first->next;
			}
		}
		ft_lstadd_back(&list, ft_lstnew((*f)(lst->content)));
		list = list->next;
		lst = lst->next;
	}
	return (first);
}
