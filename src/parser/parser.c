/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:06:00 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/16 20:51:52 by mtellal          ###   ########.fr       */
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
		token = tokenize(tlist_to_s(s->tlist, next_group));
		if (!s->clist)
			s->clist = ft_lstnew(token);
		else
			ft_lstadd_back(&s->clist, ft_lstnew(token));
		s->tlist = list_index(s->tlist, next_group);
		i++;
	}
	s->nb_cmd = nb_token_type(s->clist, ALPHANUM);
	s->nb_sep = nb_token_type(s->clist, SEPARATOR);
	s->nb_expand = nb_token_type(s->clist, EXPAND);
	clear_space(s->clist, s);
	show_command_table(s);
	if (err_separator(s->clist, s))
		return ;
	//order_input(s->clist, s);
	command_table(s->clist, s);
	show_cmd_list(s->cmd_list);
	show_command_table(s);
	clear_cmd_list(s->cmd_list, s);
}
