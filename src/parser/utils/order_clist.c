/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_clist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:24:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 15:41:27 by mtellal          ###   ########.fr       */
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
	token = ft_calloc(1, sizeof(t_token));
	token->type = type_token(*(t1->c));
        token->c = ft_strjoin_free(t1->c, t2->c, 1, 1);
	l1->content = token;
	l1->next = l2->next;
}


char	*swap_first(char **tab, int len)
{
	int	i;
	char	*t;

	i = 2;
	if (ft_strlen_tab(tab) < 2)
	{
		t = ft_strdup(tab[0]);
		free_tab(tab);
		return (t);
	}
	if (!tab || !*tab)
		return (NULL);
	t = ft_strjoin_free(tab[1], " ", 1, 0);
	t = ft_strjoin_free(t, tab[0], 1, 1);
	while (tab[i])
	{
		if (!t)
			t = ft_strjoin_free(t, tab[i], 0, 1);
		else
			t = ft_strjoin_free(t, tab[i], 1, 1);
		free(tab[i]);
		i++;
	}
	t[len] = '\0';
	free(tab);
	return (t);
}

void	order_input(t_list *list, t_input *s)
{
	t_list *plist;
	t_list *nlist;
	t_token *token;
	t_token *ptoken;
	t_token *ntoken;

	plist = NULL;
	ptoken = NULL;
	nlist = list->next;
	while (list)
	{
		token = list->content;
		if (nlist)
			ntoken = nlist->content;
		if (token->type == SEPARATOR && *token->c  == '<')
		{
			//	cas cmd < file args
			//	si file + args, on supprime args

			if (s->llist >= 3 && plist && nlist && ptoken->type != SEPARATOR && ntoken->type != SEPARATOR)
			{
				token = nlist->content;
				if (ptoken->type == ALPHANUM)
				{
					token->c = rm_first_word(token->c);
					token = list->content;
					merge_tokens(plist, nlist);
					free(token->c);
					free(token);
					list = plist;
				}
			}
			else if (!plist && nlist)
			{
				token = nlist->content;
				char **tab = ft_split(token->c, ' ');
				token->c = swap_first(tab, ft_strlen(token->c));
				s->clist = nlist;
				list = nlist;
			}
			else if (ptoken->type == SEPARATOR && nlist)
			{
				token = nlist->content;
				char **tab = ft_split(token->c, ' ');
				token->c = swap_first(tab, ft_strlen(token->c));
				plist->next = nlist;	
				list = nlist;
			}
		}
		plist = list;
		ptoken = plist->content;
		list = list->next;
		if (nlist)
			nlist = nlist->next;
	}
}
