/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/30 16:18:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*tlist_to_s(t_token *llist, int l)
{
	t_token	*list;
	int		i;
	char	*tab;

	i = 0;
	tab = ft_calloc(l + 1, sizeof(char));
	if (!tab)
		return (NULL);
	list = llist;
	while (list && i < l)
	{
		tab[i] = *list->c;
		i++;
		list = list->next;
	}
	tab[i] = '\0';
	return (tab);
}

int	next_index_group(t_token *llist)
{
	int			i;
	t_token		*list;
	enum s_type	type;

	i = 0;
	if (!llist)
		return (-1);
	list = llist;
	type = list->type;
	while (list)
	{
		if (list->type != type)
			return (i);
		i++;
		list = list->next;
	}
	return (i);
}

int	number_of_groups(t_token *list)
{
	int			i;
	t_token		*r;
	enum s_type	type;

	i = 0;
	r = list;
	while (list)
	{
		if (i == 0)
		{
			type = list->type;
			i++;
		}	
		if (list->type != type)
		{
			type = list->type;
			i++;
		}
		list = list->next;
	}
	list = r;
	return (i);
}

t_token	*tokenize(int next_group, t_token *list)
{
	t_token	*t;

	t = ft_calloc(1, sizeof(t_token));
	if (!t)
		return (NULL);
	t->c = tlist_to_s(list, next_group);
	t->type = type_token(*t->c);
	t->next = NULL;
	return (t);
}

void	parser(t_input *s)
{
	int		nb_groups;
	int		i;
	int		next_group;
	t_token	*token;
	t_token	*r;

	i = 0;
	r = s->tlist;
	nb_groups = number_of_groups(s->tlist);
	s->llist = nb_groups;
	while (i < nb_groups)
	{
		next_group = next_index_group(s->tlist);
		token = tokenize(next_group, s->tlist);
		if (!s->clist)
			s->clist = token;
		else
			ft_lstaddb_token(&s->clist, token);
		s->tlist = list_index_token(s->tlist, next_group);
		i++;
	}
	s->nb_cmd = nb_token_type(s->clist, ALPHANUM);
	s->nb_sep = nb_token_type(s->clist, SEPARATOR);
	s->tlist = r;
}
