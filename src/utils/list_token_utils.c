/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:47:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 17:56:09 by mtellal          ###   ########.fr       */
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

void	ft_lstclear_parser(t_token **list)
{
	t_token *token;

	while (*list)
	{
		if ((*list)->c)
			free((*list)->c);
		token = *list;
		*list = (*list)->next;
		free(token);
	}
	*list = NULL;
}

void	ft_lstclear_lexer(t_token **list)
{
	int	i;
	t_token	*ft;

	i = 0;
	while (*list)
	{
		if (!i && (*list)->c)
			free((*list)->c);
		i++;
		ft = *list;
		*list = (*list)->next;
		free(ft);
	}
	*list = NULL;
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
