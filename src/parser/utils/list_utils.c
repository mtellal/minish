/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 10:24:04 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 10:40:00 by mtellal          ###   ########.fr       */
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
