/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tab_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:10:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:39:10 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	nb_quotes(char *s)
{
	int		i;
	int		nb;
	char	quote;

	nb = 0;
	i = 0;
	quote = 0;
	while (s && s[i])
	{
		if (ft_belong("'\"", s[i]))
		{
			if (!quote)
			{
				nb++;
				quote = s[i];
			}
			else if (quote && s[i] == quote)
			{
				nb++;
				quote = 0;
			}
		}
		i++;
	}
	return (nb);
}

char	*merge_cell(t_coor *x, int n, char **tab)
{
	char	*sub;

	sub = NULL;
	while (n % 2 != 0 && tab[x->i + x->j])
	{
		if (x->j != 0)
			sub = ft_strjoin_free(sub, " ", 1, 0);
		sub = ft_strjoin_free(sub, tab[x->i + x->j], 1, 0);
		x->j++;
		n = nb_quotes(sub);
	}
	return (sub);
}

void	progress(t_coor *x)
{
	if (x->j)
		x->i += x->j;
	else
		x->i++;
}

char	**clear_tab(char **tab)
{
	int		n;
	t_coor	x;
	char	**final;
	char	*sub;

	final = NULL;
	sub = NULL;
	x.i = 0;
	while (tab && tab[x.i])
	{
		x.j = 0;
		n = nb_quotes(tab[x.i]);
		if (n && n % 2 != 0)
		{
			sub = merge_cell(&x, n, tab);
			final = add_tab(final, sub, 1, 1);
		}
		else
			final = add_tab(final, tab[x.i], 1, 0);
		progress(&x);
	}
	if (tab)
		free_tab(tab);
	return (final);
}
