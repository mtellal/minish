/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:11:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 11:58:08 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	match_status(char **f)
{
	*f = ft_strjoin_free(*f, ft_itoa(get_last_status()), 1, 1);
	return (2);
}

void	just_dollars(char **f, char c, int quote)
{
	if (quote || c == ' ' || c == '$' || !c)
		*f = add_char(*f, '$');
}

int	v_value(char **f, char *s, char quote, t_input *ss)
{
	int		i;
	char	*sub;
	char	*final;

	i = 0;
	final = NULL;
	if (!ft_strncmp("$?", s, 2))
		return (match_status(f));
	if (s[i] == '$')
		i++;
	while (s && s[i] && (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	sub = ft_substr(s, 0, i);
	final = value_attr(sub + 1, ss);
	if (!final && i == 1)
		just_dollars(f, s[1], quote);
	else if (final)
		*f = ft_strjoin_free(*f, final, 1, 1);
	else if (sub && !final)
		*f = ft_strjoin_free(*f, "", 1, 0);
	if (sub)
		free(sub);
	return (i);
}

char	*var_env(char *s, t_input *ss)
{
	int		i;
	int		quote;
	char	*final;

	i = 0;
	final = NULL;
	quote = 0;
	while (s && s[i])
	{
		if (!quote && ft_belong("'\"", s[i]))
			quote = s[i];
		else if (quote && ft_belong("'\"", s[i]) && quote == s[i])
			quote = 0;
		if (s[i] == '$' && quote != '\'')
			i += v_value(&final, s + i, quote, ss);
		else
			final = add_char (final, s[i++]);
	}
	if (final)
	{
		free(s);
		return (final);
	}
	else
		return (s);
}
