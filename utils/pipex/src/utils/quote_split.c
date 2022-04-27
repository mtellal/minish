/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:38:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/18 15:33:36 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	quote_block(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			return (i);
		i++;
	}
	return (0);
}

char	**add_tab(char **tab, char *s)
{
	char	**t;
	int		i;

	i = 0;
	t = malloc(sizeof(char *) * (len_tab(tab) + 2));
	while (tab && tab[i])
	{
		t[i] = ft_strdup(tab[i]);
		i++;
	}
	t[i] = ft_strdup(s);
	t[++i] = NULL;
	free(s);
	free_tab(tab);
	return (t);
}

char	**quote_split(t_pip *s, char *argv, int index)
{
	char	**tab;
	char	**tab2;
	char	**final;
	char	*sub;
	int		i2;

	sub = NULL;
	i2 = quote_block(argv + index + 1);
	ft_malloc(s, &sub, sizeof(char) * index + 1);
	ft_strlcpy(sub, argv, index);
	tab = ft_split(sub, ' ');
	free(sub);
	sub = NULL;
	ft_malloc(s, &sub, sizeof(char) * i2 + 1);
	ft_strlcpy(sub, argv + index + 1, i2 + 1);
	tab2 = add_tab(tab, sub);
	tab = ft_split(argv + index + i2 + 2, ' ');
	final = fusion_tab(tab2, tab);
	return (final);
}

void	fill_args(t_pip *s, char **argv, int nbc)
{
	int	i;
	int	quote;

	i = 0;
	while (i < nbc)
	{
		quote = quote_block(argv[2 + i]);
		if (quote)
			s->arg[i] = quote_split(s, argv[2 + i], quote);
		else
			s->arg[i] = ft_split(argv[2 + i], ' ');
		i++;
	}
}
