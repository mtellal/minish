/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:11:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 16:10:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	end_index_var(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_belong("|<> ?'\"'", s[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*value_attr(char *attr, t_input *s)
{
	t_env	*r;

	r = s->env;
	while (r)
	{
		if (!ft_strcmp(attr, r->var))
			return (r->content);
		r = r->next;	
	}
	return (NULL);
}

char	*var_value(char *s, t_input *ss)
{
	int	i;
	char	*attr;

	i = 0;
	attr = ft_substr(s + i, 0, end_index_var(s + i));
	if (attr)
		return (value_attr(attr, ss));	
	return (NULL);
}

char	*var_env(char *s, t_input *ss)
{
	int	i;
	char	*final;
	char	*value;
	int	quote;

	i = 0;
	final = NULL;
	quote = 0;
	while (1)
	{
		while (s && s[i] && !ft_belong("$'\''", s[i]))
			i++;
		if (!s[i])
		{
			if (!final)
				return (ft_substr(s, 0, i));
			else
				return (ft_strjoin_free(final, ft_substr(s, 0, i), 1, 1));	
		}
		if (s[i] == '\'')
		{
			if (quote)
				quote = 0;
			else
				quote++;
			final = ft_strjoin_free(final, ft_substr(s, 0, i + 1), 1, 1);
			s += i + 1;
			i = 0;
		}
		else
			final = ft_strjoin_free(final , ft_substr(s, 0, i), 1, 1);
		if (s[i] == '$' && !quote)
		{
			i++;
			if (s[i] && s[i] == '?')
			{
				final = ft_strjoin_free(final, ft_itoa(ss->lstatus), 1, 0);
				s += i + 1;
			}
			else
			{
				value = var_value(s + i, ss);
				if (!s[i])
					return (ft_strjoin_free(final, ft_substr(s + i, 0, i + 1), 1, 1));
				if (value)
					final = ft_strjoin_free(final, value, 1, 0);
				s += end_index_var(s + i) + i;
			}
			i = 0;
		}
		if (s[i] == '$' && quote)
			i++;
	}
}
