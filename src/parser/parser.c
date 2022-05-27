/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/27 16:09:05 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	transforme les l premiers tokens en une string 
 *	string qui va etre le contenu d'un nouveau token dans clist (commandlist)
 *	utilise pour transformer un groupe de token tlist en un seul token clist
 *	(token : a | b | c | /// d => token : abcd avec le meme )
 */

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
 *	determine le nombre de groupes dans tlist (lexer)
 *	afin de determine le nombre de token pour la clist (commandlist)
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

/*
 *	transforme une string, correspondant a plusieurs tokens de la tlist (lexer)
 *	en contenu du nouveau token dans clist (parser)
 */

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

/*
 *	remplie la liste chainee
 *	determine le nombre de groupe de type different = nb de token pour clist
 *	creer les tokens dans clist en regroupant les tokens (tlist) selon leurs types similaire 
 */

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
	clear_space(s->clist, s);
	if (err_separator(s->clist, s))
		return ;
	if (index_separator(s->clist) == -1)
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, 1, ((t_token*)s->clist->content)->c, 0)));
	else
		redirections(s->clist, s);
	layer2(s->clist, s);
	// reorder la list ou fill_args selon l id + corriger l'ecoute (genre cat) stdin  sinon cat => oo
        s->nb_cmd = ft_lstsize(s->cmd_list);
	// !!!!!!!! ne pas set les cmd direct => ls > file | wd ( ls > file) !!!!!!!!!!!
	fill_args(s->cmd_list, s);
        executer(s->cmd_list, s);
	clear_cmd_list(s->cmd_list, s);
}
