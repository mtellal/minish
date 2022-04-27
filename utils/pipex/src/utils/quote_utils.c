/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:07:58 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 17:11:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_malloc(t_pip *s, char **t, size_t m)
{
	s++;
	s--;
	*t = malloc(m);
	if (!*t)
		err("Err malloc", 1);
}

int	len_mtab(char **t1, char **t2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (t1 && t1[i])
		i++;
	while (t2 && t2[j])
	{
		i++;
		j++;
	}
	return (i);
}

char	**fusion_tab(char **t1, char **t2)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tab = malloc(sizeof(char *) * (len_mtab(t1, t2) + 1));
	while (t1 && t1[i])
	{
		tab[i] = ft_strdup(t1[i]);
		i++;
	}
	while (t2 && t2[j])
	{
		tab[i] = ft_strdup(t2[j]);
		i++;
		j++;
	}
	tab[i] = NULL;
	free_tab(t1);
	free_tab(t2);
	return (tab);
}
