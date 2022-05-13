/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 09:21:16 by mtellal          ###   ########.fr       */
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