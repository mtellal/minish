/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 15:43:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*clear_quotes(char *s)
{
	int	f_index;
	int	l_index;
	char	**tab;
	char	quote;
	int	i;

	tab = NULL;
	i = 0;
	while (1)
	{
		f_index = index_quote(s + i, 0);
		if (f_index == -1)
		{
			if (s[i])
				tab = add_tab(tab, ft_substr(s + i, 0, ft_strlen(s + i) + 1));
			return (tab_to_s(tab));
		}
		quote = s[f_index + i];
		if (!first_quote_in_word(s, i + f_index - 1, quote))
			tab = add_tab(tab, ft_substr(s + i, 0, f_index));
		else
			tab = add_tab(tab, ft_substr(s + i, 0, f_index + 1));
		i += f_index + 1;
		l_index = index_quote(s + i, quote);
		if (!last_quote_in_word(s + i + l_index + 1, quote))
			tab = add_tab(tab, ft_substr(s + i, 0, l_index));
		else
			tab = add_tab(tab, ft_substr(s + i, 0 , l_index + 1));	
		i += l_index + 1;
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
			/*ft_putstr_fd("\nclear_quote ", 2);
			cmd->args = clear_quotes(cmd->args);
			ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("\nexp_quote ", 2);
			cmd->args = expand_quotes(cmd->args);
			ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
			ft_putstr_fd(deplace_f_quote(cmd->args), 2);
			ft_putstr_fd("\n", 2);
			*/
			cmd->args = expand_quotes(clear_quotes(cmd->args));
			ft_putstr_fd("src/parser/quotes/ ", 2);
			ft_putstr_fd(cmd->args, 2);
			ft_putstr_fd("\n", 2);
		}
		list = list->next;
	}
	return (0);
}
