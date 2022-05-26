/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/26 11:06:17 by mtellal          ###   ########.fr       */
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

        tab = NULL;
        i = 0;
        while (1)
        {
                n_sp = n_space(s + i);
                if (!n_sp)
                {
                        if (s[i])
                                tab = add_tab(tab, ft_substr(s + i, 0, ft_strlen(s + i)));
                        return (tab);
                }
                tab = add_tab(tab, ft_substr(s + i, 0, n_space(s + i)));
                i += n_sp;
                while (s[i] == ' ')
                        i++;
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


char	*clear_quotes(char *s)
{
	char	**tab;
	char	*ns;
	int	f_quote;
	int	i;

	i = 0;
	tab = tab_quotes(s);
	ns = NULL;
	while (tab[i])
	{
		ft_putstr_fd("tab[i] ", 2);
		ft_putstr_fd(tab[i], 2);
		ft_putstr_fd(" clear_word ", 2);
		f_quote = index_quote(tab[i], 0);
		if (f_quote != - 1)
		{
			ns = ft_strjoin_free(ns, ft_strjoin_free(" ", clear_word(tab[i], f_quote), 0, 1), 1, 1);
			ft_putstr_fd(ns, 2);
		}
		else
			ns = ft_strjoin_free(ns, ft_strjoin_free(" ", tab[i], 0, 1), 1, 0);
		i++;
	}
	return (NULL);	
}


int	modify_quotes(t_list *list)
{
	t_cmd	*cmd;

	while (list)
	{
		cmd = list->content;
		if (index_quote(cmd->args, '\'') != -1 || index_quote(cmd->args, '\"') != -1)
		{
			ft_putstr_fd("\nclear_quote ", 2);
			cmd->args = clear_quotes(cmd->args);
			/*ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("\nexp_quote ", 2);
			cmd->args = expand_quotes(cmd->args);
			ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
			*/
			/*cmd->args = expand_quotes(clear_quotes(cmd->args));
			ft_putstr_fd("src/parser/quotes/ ", 2);
			ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
			*/
		}
		list = list->next;
	}
	return (0);
}
