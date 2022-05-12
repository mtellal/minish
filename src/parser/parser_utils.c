/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/12 14:51:40 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

#include "pipex.h"

/*
 *	retourne le maillon a la l-eme place 
 */

t_list	*list_index(t_list *list, int l)
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

char	*clist_to_s(t_list *list, int l)
{
	int	i;
	int	lentab;
	char	*tab;
	char	*s;
	t_token	*token;
	t_list	*nl;

	i = 0;
	nl = list;
	lentab = 0;
	while (list)
	{
		token = list->content;
		lentab += ft_strlen(token->c);
		list = list->next;
	}
	tab = ft_calloc(lentab + 1, 1);
	if (!tab)
		return (NULL);
	list = nl;
	while (list && i < l)
	{	
		token = list->content;
		s = ft_strdup(token->c);
		tab = ft_strjoin_free(tab, s, 1, 1);
		list = list->next;
		i++;
	}
	return (tab);
}
