/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:17:16 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	nb_type(t_token *llist, enum s_type type)
{
	int		i;
	t_token	*list;

	i = 0;
	list = llist;
	while (list && list->type == type)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_token	*tokenize(int next_group, t_token *list)
{
	t_token	*t;

	t = ft_calloc(1, sizeof(t_token));
	if (!t)
		return (NULL);
	t->c = ft_substr(list->c, 0, next_group);
	t->type = type_token(*t->c);
	t->next = NULL;
	return (t);
}

void	parser(t_input *s)
{
	int		i;
	t_token	*list;

	i = 0;
	list = s->tlist;
	while (list)
	{
		if (list->type == SEPARATOR && *list->c == '|')
		{
			ft_lstaddb_token(&s->clist, tokenize(1, list));
			list = list->next;
		}
		else
		{
			i = nb_type(list, list->type);
			ft_lstaddb_token(&s->clist, tokenize(i, list));
			while (i > 0 && list)
			{
				list = list->next;
				i--;
			}
		}
	}
	s->nb_cmd = nb_token_type(s->clist, ALPHANUM);
	s->nb_sep = nb_token_type(s->clist, SEPARATOR);
	show_parser(s);
}
