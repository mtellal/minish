/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_clist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:24:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 13:10:08 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*rm_first_word(char *s)
{
	char **tab;
	char	*t;
	int	i;

	i = 1;
	tab = ft_split(s, ' ');
	t = NULL;
	if (ft_strlen_tab(tab) <= 1)
		return (s);
	while (tab[i])
	{
		if (!t)
			t = ft_strjoin_free(t, tab[i], 0, 1);
		else
		{
			t = ft_strjoin_free(t, " ", 1, 0);
			t = ft_strjoin_free(t, tab[i], 1, 1);
		}
		i++;
	}
	return (t);
}

void	merge_tokens(t_list *l1, t_list *l2)
{
	t_token *t1;
	t_token *t2;
	t_token *token;

	t1 = l1->content;
	t2 = l2->content;
	l1->content = ft_calloc(1, sizeof(t_token));
        token = l1->content;
	token->type = type_token(*(t1->c));
        token->c = ft_strjoin_free(t1->c, t2->c, 1, 1);
	l1->next = l2->next;
}

void	order_input(t_list *list, t_input *s)
{
	t_list *plist;
	t_list *nlist;
	t_token *token;

	plist = NULL;
	nlist = list->next;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR && *token->c  == '<')
		{
			//	cas cmd < file args
			//	si file + args, on supprime args

			if (s->llist >= 3 && plist && nlist)
			{
				token = nlist->content;
				token->c = rm_first_word(token->c);
				token = list->content;
				merge_tokens(plist, nlist);
				free(token->c);
				free(token);
			}
			if (s->llist > 3 && plist && nlist)
			{

			}
		}
		plist = list;
		list = list->next;
		if (nlist)
			nlist = nlist->next;
	}
}
