/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:43:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:49:30 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	quote_inside(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_belong("'\"", s[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**quote_split(char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	if (quote_inside(s))
	{
		tab = ft_split(s, ' ');
		tab = clear_tab(tab);
		return (tab);
	}
	return (ft_split(s, ' '));
}
