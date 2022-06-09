/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:38:32 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/04 16:07:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	n_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

char	**return_tab(char **tab, char *ns, char *s, int i)
{
	if (ns)
		tab = add_tab(tab, ns, 0);
	if (s[i])
		tab = add_tab(tab, ft_substr(s + i, 0, ft_strlen(s + i)), 0);
	return (tab);
}

void	progress_next_word(char **tab, char *s, char **ns, int *i)
{
	while (s[*i] == ' ')
	{
		if (ns)
		{
			tab = add_tab(tab, *ns, 0);
			*ns = NULL;
		}
		*i += 1;
	}
}

void	nspace_in_quotes(int lfquote, char *s, char **ns, int *i)
{
	char	*sub;

	sub = NULL;
	if (s[*i + lfquote] && ft_belong("'\"", s[*i + lfquote]))
	{
		*ns = ft_strjoin_free(*ns, ft_substr(s + *i, 0, lfquote), 1, 1);
		*i += lfquote;
	}
	else
	{
		sub = ft_substr(s + *i, 0, lfquote + n_space(s + *i + lfquote));
		*ns = ft_strjoin_free(*ns, sub, 1, 1);
		*i += n_space(s + *i + lfquote) + lfquote;
	}
}

void	init_tab_quotes(t_quote *q, int *i, char ***tab, char **ns)
{
	*tab = NULL;
	*ns = NULL;
	*i = 0;
	q->l_quote = 0;
}
