/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:19:03 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 10:24:38 by mtellal          ###   ########.fr       */
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
	int		i;
	char	*attr;

	i = 0;
	attr = ft_substr(s + i, 0, end_index_var(s + i));
	if (attr)
		return (value_attr(attr, ss));
	return (NULL);
}
