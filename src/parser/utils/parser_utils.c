/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 16:13:48 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//	clear tous les tokens avec un seul espace

void	clear_space(t_list *list, t_input *s)
{
	t_list *plist;
	t_token *token;

	plist = NULL;
	while (list)
	{
		token = list->content;
		if (token->type == ALPHANUM)
		{
			if (only_space(token->c))
			{
				if (plist)
					plist->next = list->next;
				else
					s->clist = list->next;
				free(token->c);
				free(token);
			}
		}
		plist = list;
		list = list->next;
	}
}

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
