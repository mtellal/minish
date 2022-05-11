/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/10 14:35:08 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

#include "pipex.h"

/*
 *	retourne le maillon a la l-eme place 
 */

t_list	*tlist_index(t_list *list, int l)
{
	int	i;

	i = 0;
	if (!list)
		return (NULL);
	while (list && i < l)
	{
		list = list->next;
		i++;
	}
	return (list);
}


int	nb_token_type(t_list *list, enum s_type type)
{
	int	i;
	t_token	*token;

	i = 0;
	while (list)
	{
		token = list->content;
		if (token->type == type)
			i++;
		list = list->next;
	}
	return (i);
}

void	pipex_integration(t_input *s)
{
	char	**tab;
	int		i;
	t_token	*token;

	i = 0;
	s->llist = nb_token_type(s->clist, ALPHANUM);
	printf("%i nb types\n",s->llist); 
	tab = malloc(sizeof(char*) * (s->llist + 1));
	if (!tab)
		return ;
	while (s->clist)
	{
		token = s->clist->content;
		if (token->type == ALPHANUM)
		{
			tab[i] = token->c;
			i++;
		}
		s->clist = s->clist->next;
	}
	tab[i] = NULL;
	i = 0;
	printf("tab send to pipex\n");
	while (i < s->llist)
	{
		printf("%s	", tab[i]);
		i++;
	}
	printf("\n");
}
