/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/07 10:36:12 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_env	*previous_already_exists(t_env *n, t_env *env)
{
	t_env	*penv;
	t_env	*lenv;

	penv = NULL;
	lenv = env;
	while (env)
	{
		if (!ft_strcmp(env->var, n->var) && penv)
		{
			penv->next = env->next;
			if (env->content)
				free(env->content);
			if (env->var)
				free(env->var);
			free(env);
			env = lenv;
			return (penv);
		}
		penv = env;
		env = env->next;
	}
	env = lenv;
	return (NULL);
}

int	verif_args(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!isalnum(tab[i][j]))
				return (msg_err_unset(tab[i]));
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_unset(char **args, t_input *s)
{
	int		i;
	t_env	*n;
	t_env	*pe;
	t_env	*r;

	n = NULL;
	pe = NULL;
	r = s->env;
	i = 1;
	if (verif_args(args) != -1)
	{
		while (args && args[i])
		{
			n = str_to_env(args[i]);
			pe = previous_already_exists(n, s->env);
			if (!s->env && !pe)
				s->env = n;
			else
				free_env(&n);
			i++;
		}
	}
	s->env = r;
	return (return_status(0, s));
}
