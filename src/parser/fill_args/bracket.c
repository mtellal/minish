/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:17:39 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 09:30:41 by mtellal          ###   ########.fr       */
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

static int	merge_cell(char **args, int i, char **sub, char ***tab)
{
	while (args[i] && !end_bracket(args[i]))
		*sub = ft_strjoin_free(*sub, args[i++], 1, 0);
	if (args[i])
		*sub = ft_strjoin_free(*sub, args[i], 1, 0);
	if (ft_strlen(*sub) > 2 && ft_belong("'", *sub[0]))
		*sub = ft_substr_free(*sub, 1, ft_strlen(*sub) - 2, 1);
	*tab = add_tab(*tab, *sub, 1, 1);
	return (i);
}

/*
 *	deal the ' xxx { script }'
 *	Join the script after ft_split
 */

char	**join_brackets(char **args)
{
	int		i;
	char	**tab;
	char	*sub;

	i = 0;
	tab = NULL;
	sub = NULL;
	while (args && args[i])
	{
		if (!pair_brackets(args[i]))
			i = merge_cell(args, i, &sub, &tab);
		else
		{
			if (ft_strlen(args[i]) > 2 && ft_belong("'", args[i][0]))
				sub = ft_substr_free(sub, 1,
						ft_strlen(args[i]) - 2, 1);
			tab = add_tab(tab, args[i], 1, 0);
		}
		if (args[i])
			i++;
	}
	return (tab);
}
