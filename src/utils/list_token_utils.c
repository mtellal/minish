/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:47:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:07:21 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    free_token(t_token **token)
{
        if (!*token)
                return ;
        if (*token && (*token)->c)
                free((*token)->c);
        if (*token)
		free(*token);
}


void    ft_lstaddb_token(t_token **lst, t_token *n)
{
        t_token *r;

        if (!n)
                return ;
        if (!lst || !*lst)
                *lst = n;
        else
        {
                r = *lst;
                while ((*lst)->next)
                        *lst = (*lst)->next;
                (*lst)->next = n;
                *lst = r;
        }
}

int	ft_lstsize_token(t_token *llist)
{
	int		i;
	t_token *list;

	i = 0;
	list = llist;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_token *list_index_token(t_token *token, int l)
{
        int     i;
	t_token	*list;

        i = 0;
        list = token;
	if (!list || l < 0)
                return (NULL);
        while (list && i < l)
        {
                list = list->next;
                i++;
        }
        return (list);
}
