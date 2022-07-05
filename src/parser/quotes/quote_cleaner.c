/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:27:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:48:24 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	modify_var_env(char **tab, t_input *s)
{
	int		i;
	char	*var;

	i = 0;
	var = NULL;
	while (tab && tab[i])
	{
		if (!ft_belong("'", tab[i][0]))
		{
			var = var_env(tab[i], s);
			tab[i] = var;
		}
		i++;
	}
}

char	*clear_word(char *s)
{
	char	*final;
	char	quote;
	t_coor	x;

	x.i = 0;
	quote = 0;
	if (!s || !*s)
		return (NULL);
	final = ft_strdup("'");
	while (s && s[x.i])
	{
		if (!quote && ft_belong("'\"", s[x.i]))
			quote = s[x.i];
		else if (quote && ft_belong("'\"", s[x.i]) && s[x.i] == quote)
			quote = 0;
		else
			final = add_char(final, s[x.i]);
		x.i++;
	}
	final = ft_strjoin_free(final, "'", 1, 0);
	if (s)
		free(s);
	return (final);
}

char	*merge_quotes(char **tab, t_input *ss)
{
	int		n;
	int		i;
	char	**final;
	char	*s;

	s = NULL;
	i = 0;
	n = 0;
	final = clear_tab(tab);
	modify_var_env(final, ss);
	while (final && final[i])
	{
		n = nb_quotes(final[i]);
		if (n)
			final[i] = clear_word(final[i]);
		s = ft_strjoin_free(s, final[i], 1, 0);
		if (ft_strlen(final[i]) >= 1 && !ft_belong("'", final[i][0])
				&& type_token(final[i][0]) == ALPHANUM)
			s = ft_strjoin_free(s, " ", 1, 0);
		if (ft_strlen(final[i]) >= 2 && ft_belong("'", final[i][0])
				&& type_token(final[i][0]) == ALPHANUM)
			s = ft_strjoin_free(s, " ", 1, 0);
		i++;
	}
	if (final)
		free_tab(final);
	return (s);
}

char	*clear_str(char *s, t_input *ss)
{
	char	*final;
	char	**tab;

	tab = NULL;
	final = remove_empty_quotes(s);
	if (final)
	{
		tab = ft_split(final, ' ');
		free(final);
		final = merge_quotes(tab, ss);
	}
	return (final);
}

void	quote_cleaner(t_input *s)
{
	t_token	*list;

	list = s->clist;
	while (list)
	{
		if (quote_inside(list->c))
			list->c = clear_str(list->c, s);
		else
			list->c = var_env(list->c, s);
		list = list->next;
	}
}
