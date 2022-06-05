/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:01:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 18:37:04 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	affiche chaque token dans la tlist
 *	char c + type
 */

void	show_command_table(t_input *s)
{
	t_token	*r;

	r = s->clist;
	while (s->clist)
	{
		printf(" '%s' ", s->clist->c);
		s->clist = s->clist->next;
	}
	s->clist = r;
	printf("\n");
}
