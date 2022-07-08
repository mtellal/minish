/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:57:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 09:31:35 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**rm_quotes_word(char **tab)
{
	int		i;
	char	**final;
	char	*sub;

	i = 0;
	final = NULL;
	sub = NULL;
	while (tab && tab[i])
	{
		if (ft_strlen(tab[i]) > 2 && tab[i][0] == '\'')
		{
			sub = ft_substr(tab[i], 1, ft_strlen(tab[i]) - 2);
			final = add_tab(final, sub, 1, 1);
		}	
		else
			final = add_tab(final, tab[i], 1, 0);
		i++;
	}
	if (tab)
		free_tab(tab);
	return (final);
}

void	fill_args(t_cmd *cmd, t_input *s)
{
	int		i;
	int		bracket;
	char	**args;

	i = 0;
	while (i < s->nb_cmd)
	{
		bracket = 0;
		cmd = cmd_index(s->cmd, i);
		if (cmd && cmd->args)
		{
			if (bracket_inside(cmd->args))
				bracket = 1;
			args = quote_split(cmd->args);
			if (bracket)
				args = join_brackets(args);
			cmd->cmd_args = rm_quotes_word(args);
		}
		i++;
	}
}
