/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 18:49:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	index_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (c == 0)
		{
			if (s[i] == '\'' || s[i] == '\"')
				return (i);
		}
		else if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int     msg_err_quote(void)
{
        ft_putstr_fd("error: unclosed quotes\n", 2);
        return (-1);
}

int	verif_pair_of_quotes(char *s)
{
	int	i;
	char	quote;
	int	nquote;

	i = 0;
	quote = 0;
	nquote = 0;
	while (s && s[i])
	{
		if (ft_belong("'\'''\"'", s[i]))
		{
			if (!nquote)
			{
				nquote++;
				quote = s[i];
			}
			else if (quote == s[i])
			{
				quote = 0;
				nquote--;
			}
		}
		i++;
	}
	if (s && quote && !s[i])
		return (msg_err_quote());
	return (0);
}
