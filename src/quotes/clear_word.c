/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:39:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 15:24:53 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_first_char(int f_quote, char *ns, char *s, int i)
{
	if (!i && s[i] != s[f_quote])
	{
		if (s[i + f_quote] == '\'')
			ns = ft_strjoin_free("'", ft_substr(s + i, 0, f_quote), 0, 1);
		else
			ns = ft_strjoin_free("\"", ft_substr(s + i, 0, f_quote), 0, 1);
	}
	else if (!i)
		ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote + 1), 1, 1);
	else if (f_quote != -1)
		ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote), 1, 1);
}

void	set_i_fquote(int *i, int *fquote, int vi, int vfquote)
{
	*i += vi;
	*fquote = vfquote;
}

char	*no_more_quotes(char *ns, char *s, int i, char _quote)
{
	if (s[i])
		ns = ft_strjoin_free(ns, ft_substr(s + i, 0, ft_strlen(s + i)), 1, 1);
	if (_quote == '\'')
		ns = ft_strjoin_free(ns, "'", 1, 0);
	else
		ns = ft_strjoin_free(ns, "\"", 1, 0);
	return (ns);
}

void	init_clear_word(int *i, char *quote, char **ns)
{
	*i = 0;
	*quote = 0;
	*ns = NULL;
}
