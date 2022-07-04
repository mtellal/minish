/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:42:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 18:03:19 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char    *join_tab(char **tab, int j, int ftab)
{
        char    *t;

        t = NULL;
        while (tab[j])
        {
                if (!t)
                        t = ft_strjoin_free(t, tab[j], 0, 0);
                else
                        t = ft_strjoin_free(t, tab[j], 1, 0);
                t = ft_strjoin_free(t, " ", 1, 0);
                j++;
        }
        if (tab && ftab)
                free_tab(tab);
        return (t);
}

void	 print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_putchar_fd('[', 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(']', 1);
		ft_putstr_fd("	'", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putendl_fd("'", 1);
		i++;
	}
}
