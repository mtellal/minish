/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 15:22:48 by mtellal          ###   ########.fr       */
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

int	msg_err_quote(void)
{
	ft_putstr_fd("error: unclosed quotes\n", 2);
	return (-1);
}

void	set_quote_nquote(char *quote, int *nquote, char vquote, int vnquote)
{
	*quote = vquote;
	*nquote = vnquote;
}

int	verif_pair_of_quotes(char *s)
{
	int		i;
	int		nquote;
	char	quote;

	i = 0;
	quote = 0;
	nquote = 0;
	while (s && s[i])
	{
		if (ft_belong("'\'''\"'", s[i]))
		{
			if (!nquote)
				set_quote_nquote(&quote, &nquote, s[i], nquote + 1);
			else if (quote == s[i])
				set_quote_nquote(&quote, &nquote, 0, nquote - 1);
		}
		i++;
	}
	if (s && quote && !s[i])
		return (msg_err_quote());
	return (0);
}
