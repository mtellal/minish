/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 14:53:06 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
