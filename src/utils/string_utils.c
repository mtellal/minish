/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:16:50 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 12:51:06 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*add_char(char *s, char c)
{
	int		i;
	char	*tab;

	i = 0;
	tab = calloc(ft_strlen(s) + 2, sizeof(char));
	if (!tab)
		return (NULL);
	while (s && s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i++] = c;
	tab[i] = '\0';
	if (s)
		free(s);
	return (tab);
}

int	ft_belong(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
