/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 21:06:31 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	transforme les l premiers tokens en une string 
 */

char	*tlist_to_s(t_list	*list, int l)
{
	int	i;
	char	*tab;
	t_token	*token;

	i = 0;
	tab = malloc(sizeof(char) * l);
	if (!tab)
		return (NULL);
	while (list && i < l)
	{
		token = list->content;
		tab[i] = *token->c;
		i++;
		list = list->next;
	}
	tab[i] = '\0';
	return (tab);
}

/*
 *	renvoie l'index du prochain type different 
 *	et donc l'index du prochain groupe de type (s_type->type) similaire
 */

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

/*
 *	Le but du parser =>
 *	Transformer la liste de token en plusieurs groupe et selon leurs type
 */

int	number_of_groups(t_list	*list)
{
	int	i;
	t_token	*token;
	enum s_type	type;

	i = 0;
	while (list)
	{
		token = list->content;
		if (i == 0 && token->type)
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

/*
 *	creer un tableau de de string
 *	regroupe les tokens avec un type similaire
 *	et remplie le tableau avec ces groupes
 */
/*
void	parser(t_input *s)
{
	int	nb_groups;
	int	i;
	int	next_groups;

	i = 0;
	nb_groups = number_of_groups(s->tlist);
	s->table = malloc(sizeof(char*) * nb_groups);
	if (nb_groups == 1)
		s->table[0] = tlist_to_s(s->tlist, s->llist);
	else
	{
		while (i < nb_groups)
		{
			next_groups = next_index_group(s->tlist);
			if (next_groups != -1)
			{
				s->table[i] = tlist_to_s(s->tlist, next_groups);
				s->tlist = tlist_index(s->tlist, next_groups);
			}
			i++;
		}	
	}
	s->table[nb_groups] = NULL;	
}
*/
t_token	*tokenize(char *s)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token || !s)
		return (NULL);
	token->c = s;
	token->type = type_token(*s);
	return (token);
}

void	parser(t_input *s)
{
	int	nb_groups;
	int	i;
	int	next_group;
	t_token	*token;

	i = 0;
	nb_groups = number_of_groups(s->tlist);
	while (i < nb_groups)
	{
		next_group = next_index_group(s->tlist);
		token = tokenize(tlist_to_s(s->tlist, next_group));
		if (!s->clist)
			s->clist = ft_lstnew(token);
		else
			ft_lstadd_back(&s->clist, ft_lstnew(token));
		s->tlist = tlist_index(s->tlist, next_group);
		i++;
	}
}
