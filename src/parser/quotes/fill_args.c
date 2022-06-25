/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/09 18:08:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**tab_quotes(char *s)
{
	t_quote	q;
	int		i;
	int		n_sp;
	char	**tab;
	char	*ns;

	init_tab_quotes(&q, &i, &tab, &ns);
	while (1)
	{
		q.f_quote = index_quote(s + i, 0);
		n_sp = n_space(s + i);
		if (q.f_quote != -1)
			q.l_quote = index_quote(s + i + q.f_quote + 1, s[q.f_quote + i]);
		else
			return (return_tab(tab, ns, s, i));
		if (q.f_quote > 0 && n_sp < q.f_quote)
		{
			tab = add_tab(tab, ft_substr(s + i, 0, n_sp), 1, 1);
			i += n_sp;
		}
		else if (n_sp > q.f_quote)
			nspace_in_quotes(q.l_quote + q.f_quote + 2, s, &ns, &i);
		progress_next_word(&tab, s, &ns, &i);
	}
	return (NULL);
}	

char	*clear_word(char *s, int f_quote)
{
	int		l_quote;
	int		i;
	char	*ns;
	char	_quote;
	char	quote;

	init_clear_word(&i, &quote, &ns);
	_quote = s[f_quote];
	while (1)
	{
		quote = s[i + f_quote];
		set_first_char(f_quote, &ns, s, i);
		i += f_quote + 1;
		l_quote = index_quote(s + i, quote);
		ns = ft_strjoin_free(ns, ft_substr(s + i, 0, l_quote), 1, 1);
		if (s[i + l_quote + 1] && ft_belong("'\"", s[i + l_quote + 1]))
			set_i_fquote(&i, &f_quote, l_quote + 2, -1);
		else
			set_i_fquote(&i, &f_quote, l_quote + 1, 0);
		f_quote = index_quote(s + i, 0);
		if (f_quote == -1 || !s[i + l_quote + 1])
			return (no_more_quotes(ns, s, i, _quote));
	}
	return (NULL);
}

void	clear_quotes(char *s, char ***args)
{
	int		f_quote;
	int		i;
	char	**tab;
	char	*c_word;

	if (!s)
	{
		*args = NULL;
		return ;
	}
	i = 0;
	tab = tab_quotes(s);
	while (tab[i])
	{
		f_quote = index_quote(tab[i], 0);
		if ((ft_strlen(tab[i]) == 2 && tab[i][0] == tab[i][1]) || f_quote == -1)
			*args = merge_tab(*args, ft_split(tab[i], ' '));
		else if (f_quote != -1)
		{
			c_word = clear_word(tab[i], f_quote);
			c_word = ft_substr(c_word, 1, ft_strlen(c_word + 1) - 1);
			*args = add_tab(*args, c_word, 0, 1);
		}
		i++;
	}
}

int	fill_args(t_cmd *list, t_input *s)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	while (i < s->nb_cmd)
	{
		cmd = (cmd_index(list, i));
		clear_quotes(cmd->args, &cmd->cmd_args);
		i++;
	}
	return (0);
}
