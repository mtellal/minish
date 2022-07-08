/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:19:03 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 13:31:16 by mtellal          ###   ########.fr       */
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
			return (ft_strdup(r->content));
		r = r->next;
	}
	return (NULL);
}
