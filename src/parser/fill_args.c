/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:57:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 16:38:18 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	end_bracket(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '}')
			return (1);
		i++;
	}
	return (0);
}

int	pair_brackets(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s && s[i])
	{
		if (s[i] == '{' && n % 2 == 0)
			n++;
		if (s[i] == '}' && n % 2 != 0)
			n++;
		i++;
	}
	if (n > 0 && n % 2 != 0)
		return (0);
	else
		return (1);
}

/*
 *	deal the ' xxx { script }'
 *	it join the script otherwise cmd like awk print error msg
 *	example: awk '{print $1}' file 
 *	transform [0] = awk, [1] = '{print, [2] = $1}', [3] file
 *	in 	  [0] = awk, [1] = '{print $1}', [2] = file
 */

char	**join_brackets(char **args)
{
	int	i;
	char	**tab;
	char	*sub;

	i = 0;
	tab = NULL;
	sub = NULL;
	while (args && args[i])
	{
		if (!pair_brackets(args[i]))
		{
			while (args[i] && !end_bracket(args[i]))
				sub = ft_strjoin_free(sub, args[i++], 1, 0);
			if (args[i])
				sub = ft_strjoin_free(sub, args[i], 1, 0);
			if (ft_strlen(sub) > 2 && ft_belong("'", sub[0]))
				sub = ft_substr_free(sub, 1, ft_strlen(sub) - 2, 1);
			tab = add_tab(tab, sub, 1, 1);
		}
		else
		{
			if (ft_strlen(args[i]) > 2 && ft_belong("'", args[i][0]))
                                sub = ft_substr_free(sub, 1, ft_strlen(args[i]) - 2, 1);
			tab = add_tab(tab, args[i], 1, 0);
		}
		if (args[i])
			i++;
	}
	return (tab);
}

char	**rm_quotes_word(char **tab)
{
	char	**final;
	int	i;
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

int	bracket_inside(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_belong("{}", s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	fill_args(t_cmd *cmd, t_input *s)
{
	int	i;
	char	**args;
	int	bracket;

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
