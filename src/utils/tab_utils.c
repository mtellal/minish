/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/25 12:10:35 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char    **add_tab(char **tab, char *s)
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
                free(tab[i]);
                i++;
        }
        ntab[i++] = ft_strdup(s);
        ntab[i] = NULL;
        free(s);
	return (ntab);
}

char    *tab_to_s(char **tab)
{
        char    *s;
        int     i;

        i = 0;
        s = NULL;
	while (tab[i])
        {
                s = ft_strjoin_free(s, tab[i], 1, 1);
                i++;
        }
	free(tab);
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

