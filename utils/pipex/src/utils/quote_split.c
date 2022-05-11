/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:38:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/10 16:34:27 by mtellal          ###   ########.fr       */
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
	if (!t)
		return (NULL);
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

char	**quote_split(char *argv, int index)
{
	char	**tab;
	char	**tab2;
	char	**final;
	char	*sub;
	int		i2;

	sub = NULL;
	i2 = quote_block(argv + index + 1);
	sub = malloc(sizeof(char) * index + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, argv, index);
	tab = ft_split(sub, ' ');
	free(sub);
	sub = NULL;
	sub = malloc(sizeof(char) * i2 + 1);
	if (!sub)
		return (NULL);
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
		quote = quote_block(argv[s->pos_cmd + i]);
		if (quote)
			s->arg[i] = quote_split(argv[s->pos_cmd + i], quote);
		else
			s->arg[i] = ft_split(argv[s->pos_cmd + i], ' ');
		i++;
	}
}
