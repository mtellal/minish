/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/07 16:02:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**merge_tab(char **tab, char **tab2)
{
	char	**final;
	int	i;
	int	j;

	j = 0;
	i = 0;
	final = ft_calloc(ft_strlen_tab(tab) + ft_strlen_tab(tab2) + 1, sizeof(char*));
	while (tab && tab[i])
	{
		final[i] = ft_strdup(tab[i]);
		i++;
	}
	while (tab2 && tab2[j])
	{
		final[i] = ft_strdup(tab2[j]);
		j++;
		i++;
	}
	final[i] = NULL;
	if (tab)
		free_tab(tab);
	if (tab2)
		free_tab(tab2);
	return (final);
}

char    **add_tab(char **tab, char *s, int ftab, int fs)
{
        char    **ntab;
        int     i;

        i = 0;
	if (!s || !*s)
		return (NULL);
        ntab = ft_calloc(ft_strlen_tab(tab) + 2, sizeof(char*));
        while (tab && tab[i])
        {
                ntab[i] = ft_strdup(tab[i]);
                i++;
        }
        ntab[i++] = ft_strdup(s);
        ntab[i] = NULL;
        if (s && fs)
		free(s);
	if (tab && ftab)
		free_tab(tab);
	return (ntab);
}

char    *tab_to_s(char **tab, int f)
{
        char    *s;
        int     i;

        i = 0;
        s = NULL;
	while (tab && tab[i])
        {
                s = ft_strjoin_free(s, tab[i], 1, 0);
                i++;
        }
	if (tab && f)
		free_tab(tab);
        return (s);
}

int     ft_strlen_tab(char **tab)
{
        int     i;

        i = 0;
        while (tab && tab[i])
                i++;
        return (i);
}

void    free_tab(char **tab)
{
        int     i;

        i = 0;
        while (tab[i])
        {
                free(tab[i]);
                i++;
        }
        free(tab);
}

