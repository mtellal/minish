/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:43:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/03 17:48:38 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**quote_split(char *s)
{
	char	**tab;
	int	i;

	i = 0;
	tab = NULL;
	tab = ft_split(s, ' ');
	tab = clear_tab(tab);
	return (tab);
}
