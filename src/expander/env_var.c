/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:11:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/08 15:04:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	var_match(int *i, char **s, char **final, t_input *ss)
{
	char	*value;

	value = NULL;
	*i += 1;
	if ((*s)[*i] == ' ')
	{
		*final = ft_strjoin_free(*final, ft_substr(*s + *i - 1, 0, 1), 1, 1);
		*s += *i;
	}
	else if ((*s)[*i] && (*s)[*i] == '?')
	{
		*final = ft_strjoin_free(*final, ft_itoa(ss->lstatus), 1, 0);
		*s += *i + 1;
	}
	else
	{
		if (!(*s)[*i])
			*final = ft_strjoin_free(*final, ft_substr(*s + *i, 0, *i + 1), 1, 1);
		else
		{
			value = var_value(*s + *i, ss);
			if (value)
				*final = ft_strjoin_free(*final, value, 1, 0);
			*s += end_index_var(*s + *i) + *i;
		}
	}
	*i = 0;
}

void	quote_match(int i, int *quote, char **final, char **s)
{
	if (*quote)
		*quote = 0;
	else
		(*quote)++;
	*final = ft_strjoin_free(*final, ft_substr(*s, 0, i + 1), 1, 1);
	*s += i + 1;
}

char	*null_match(int i, char *final, char *s)
{
	if (!final)
		return (ft_substr(s, 0, i));
	else
		return (ft_strjoin_free(final, ft_substr(s, 0, i), 1, 1));
}

char	*var_env(char *s, t_input *ss)
{
	int		i;
	int		quote;
	char	*final;

	i = 0;
	final = NULL;
	quote = 0;
	while (1)
	{
		while (s && s[i] && !ft_belong("$'\''", s[i]))
			i++;
		if (!s[i])
			return (null_match(i, final, s));
		if (s[i] == '\'')
			quote_match(i, &quote, &final, &s);
		else
		{
			final = ft_strjoin_free(final, ft_substr(s, 0, i), 1, 1);
			s += i;
		}
		i = 0;
		if (*s == '$' && !quote)
			var_match(&i, &s, &final, ss);
		if (s[i] == '$' && quote)
			i++;
	}
}
