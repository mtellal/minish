/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 20:55:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*tlist_to_s(t_list	*list, int l)
{
	int	i;
	char	*tab;
	t_token	*token;

	i = 0;
	tab = ft_calloc(l, sizeof(char));
	if (!tab)
		return (NULL);
	while (list && i < l)
	{
		token = list->content;
		tab[i] = *token->c;
		i++;
		list = list->next;
	}
	while (i < l)
		tab[i] = '\0';
	tab[l] = '\0';
	return (tab);
}

int	next_index_group(t_list	*list)
{
	int	i;
	t_token	*token;
	enum s_type	type;

	 i = 0;
	 token = list->content;
	 type = token->type;
	 if (!list)
		 return (-1);
	 while (list)
	 {
		 token = list->content;
		if (token->type != type)
			return (i);
		i++;
		list = list->next;
	 }
	 return (i);
}

int	number_of_groups(t_list	*list)
{
	int	i;
	t_token	*token;
	enum s_type	type;

	i = 0;
	while (list)
	{
		token = list->content;
		if (i == 0 && token)
		{
			type = token->type;
			i++;
		}	
		if (token->type != type)
		{
			type = token->type;
			i++;
		}
		list = list->next;
	}
	return (i);
}

t_token	*tokenize(int	next_group, t_list *list)
{
	t_token	*t;
	char	*s;

	t = ft_calloc(1, sizeof(t_token));
	if (!t)
		return (NULL);
	s = tlist_to_s(list, next_group);
	t->c = s;
	t->type = type_token(*s);
	return (t);
}

void	parser(t_input *s)
{
	int	nb_groups;
	int	i;
	int	next_group;
	t_token	*token;

	i = 0;
	nb_groups = number_of_groups(s->tlist);
	s->llist = nb_groups;
	while (i < nb_groups)
	{
		next_group = next_index_group(s->tlist);
		token = tokenize(next_group, s->tlist);
		if (!s->clist)
			s->clist = ft_lstnew(token);
		else
			ft_lstadd_back(&s->clist, ft_lstnew(token));
		s->tlist = list_index(s->tlist, next_group);
		i++;
	}
	s->nb_cmd = nb_token_type(s->clist, ALPHANUM);
	s->nb_sep = nb_token_type(s->clist, SEPARATOR);
}
