/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:01:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 20:03:26 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	show_command_table(t_input *s)
{
	int	i;
	t_list	*list;
	t_token	*token;

	i = 0;
	list = s->clist;
	while (list)
	{
		token = list->content;
		printf(" '%s' ", token->c);
		list = list->next;
		i++;
	}
	printf("\n");
}
