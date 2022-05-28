/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/28 18:15:52 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     n_space(char *s)
{
        int     i;

        i = 0;
        while (s[i])
        {
                if (s[i] == ' ')
                        return (i);
                i++;
        }
        return (i);
}

char	**tab_quotes(char *s)
{
	 char    **tab;
        int     i;
        int     n_sp;
	char	quote;
	int	f_quote;
	int	l_quote;
	char	*ns;

        tab = NULL;
        i = 0;
	quote = 0;
	l_quote = 0;
        ns = NULL;
	while (1)
        {
                f_quote = index_quote(s + i, 0);
		n_sp = n_space(s + i);
		if (f_quote != -1)
		{
			quote = s[f_quote + i];
			l_quote = index_quote(s + i + f_quote + 1, quote);
		}
		else
                {
			if (ns)
				tab = add_tab(tab, ns, 0);
                        if (s[i])
                                tab = add_tab(tab, ft_substr(s + i, 0, ft_strlen(s + i)), 0);
                        return (tab);
                }
		if (f_quote > 0 && n_sp < f_quote)
		{
			tab = add_tab(tab, ft_substr(s + i, 0, n_sp), 0);
			i += n_sp;
		}
		else if (n_sp > f_quote)
                {
			if (s[i + f_quote + l_quote + 2] && ft_belong("'\"", s[i + f_quote + l_quote + 2]))
			{
				ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote + l_quote + 2), 1, 1);
				i += f_quote + l_quote + 2;
			}
			else
			{
				ns = ft_strjoin_free(ns, ft_substr(s + i , 0, f_quote + l_quote + 2 + n_space(s + i + f_quote + l_quote + 2)), 1, 1);
				i += n_space(s + i + l_quote + f_quote + 2) + l_quote + f_quote + 2;
			}
		}
		while (s[i] == ' ')
		{
			if (ns)
			{
				tab = add_tab(tab, ns, 0);
				ns = NULL;
			}
			i++;
		}
        }
        return (NULL);

}	

char	*clear_word(char *s, int f_quote)
{
	int	l_quote;
	char	*ns;
	char	_quote;
	char	quote;
	int	i;

	i = 0;
	quote = 0;
	_quote = s[f_quote];
	ns = NULL;
	while (1)
	{
		quote = s[i + f_quote];
		if (i == 0 && s[i] != quote)
		{
			if (quote == '\'')
				ns = ft_strjoin_free("'", ft_substr(s + i, 0, f_quote), 0, 1);
			else
				ns = ft_strjoin_free("\"", ft_substr(s + i, 0, f_quote), 0, 1);
		}
		else if (i == 0)
			ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote + 1), 1, 1);
		else if (f_quote != -1)
			ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote), 1, 1);
		i += f_quote + 1;
		l_quote = index_quote(s + i, quote);
		ns = ft_strjoin_free(ns, ft_substr(s + i, 0, l_quote), 1, 1);
		if (s[i + l_quote + 1] && ft_belong("'\"", s[i + l_quote + 1]))
		{
			i += l_quote + 2;
			f_quote = -1;
		}
		else
		{
			i += l_quote + 1;
			f_quote = 0;
		}
		if (f_quote != -1)
		{
			f_quote = index_quote(s + i, 0);
			if (f_quote == -1)
			{
				if (s[i])
					ns = ft_strjoin_free(ns, ft_substr(s + i, 0, ft_strlen(s + i)), 1, 1);
				if (_quote == '\'')
					ns = ft_strjoin_free(ns, "'", 1, 0);
				else
					ns = ft_strjoin_free(ns, "\"", 1, 0);
				return (ns);
			}
		}
	}
	return (NULL);
}


void	clear_quotes(char *s, char ***args)
{
	char	**tab;
	int	f_quote;
	int	i;
	char	*c_word;

	if (!s)
		*args = NULL;
	i = 0;
	tab = tab_quotes(s);
	while (tab[i])
	{
		f_quote = index_quote(tab[i], 0);
		if ((ft_strlen(tab[i]) == 2 && tab[i][0] == tab[i][1]) || f_quote == -1)
			*args = merge_tab(*args, ft_split(tab[i], ' ')); 
		else if (f_quote != - 1)
		{
			c_word = clear_word(tab[i], f_quote);
			*args = add_tab(*args, ft_substr(c_word, 1, ft_strlen(c_word + 1) - 1), 0);
		}
		i++;
	}
}


int	fill_args(t_list *list, t_input *s)
{
	int	i;
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
