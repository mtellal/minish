/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/03 10:14:56 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*tlist_to_s(t_token *list, int l)
{
	t_token	*r;
	int		i;
	char	*tab;

	i = 0;
	tab = ft_calloc(l, sizeof(char));
	if (!tab)
		return (NULL);
	r = list;
	while (list && i < l)
	{
		tab[i] = *list->c;
		i++;
		list = list->next;
	}
	while (i < l)
		tab[i] = '\0';
	tab[l] = '\0';
	list = r;
	return (tab);
}

int	next_index_group(t_token *list)
{
	int			i;
	t_token		*token;
	enum s_type	type;

	i = 0;
	if (!list)
		return (-1);
	type = list->type;
	while (list)
	{
		token = list;
		if (token->type != type)
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
	char	*s;

	t = ft_calloc(1, sizeof(t_token));
	if (!t)
		return (NULL);
	s = tlist_to_s(list, next_group);
	t->c = s;
	t->type = type_token(*s);
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
