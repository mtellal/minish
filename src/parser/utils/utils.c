/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:18:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 18:14:50 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	index_separator(t_token *list)
{
	int	i;
	t_token	*r;

	i = 0;
	r = list;
	while (list)
	{
		if (list->type == SEPARATOR && !only_space(list->c))
			return (i);
		list = list->next;
		i++;
	}
	list = r;
	return (-1);
}

int     nb_token_type(t_token *list, enum s_type type)
{
        int     i;
        t_token *r;

        i = 0;
	r = list;
        while (list)
        {
                if (list->type == type)
                        i++;
                list = list->next;
        }
	list = r;
        return (i);
}
