/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:43:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/08 17:12:26 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	quote_inside(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_belong("'\"", s[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**quote_split(char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	if (quote_inside(s))
	{
		tab = ft_split(s, ' ');
		tab = clear_tab(tab);
		return (tab);
	}
	return (ft_split(s, ' '));
}

void	add_word_space(char **s, char **final, int i)
{
	if (ft_strlen(final[i]) >= 1 && !ft_belong("'", final[i][0])
			&& type_token(final[i][0]) == ALPHANUM)
		*s = ft_strjoin_free(*s, " ", 1, 0);
	if (ft_strlen(final[i]) >= 2 && ft_belong("'", final[i][0])
			&& type_token(final[i][0]) == ALPHANUM)
		*s = ft_strjoin_free(*s, " ", 1, 0);
}
