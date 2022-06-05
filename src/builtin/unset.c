/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 10:35:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_env	*previous_already_exists(t_env *n, t_env *env)
{
	t_env	*penv;

	penv = NULL;
	while (env)
	{
		if (!ft_strcmp(env->var, n->var) && penv)
			return (penv);
		penv = env;
		env = env->next;
	}
	return (NULL);
}

int	lst_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	free_tenv(t_env *e)
{
	if (!e)
		return ;
	if (e->var)
		free(e->var);
	if (e->content)
		free(e->content);
	free(e);
}

void	ft_unset(char **args, t_input *s)
{
	int		i;
	t_env	*n;
	t_env	*pe;
	t_env	*sub;
	t_env	*r;

	n = NULL;
	pe = NULL;
	r = s->env;
	i = 1;
	while (args && args[i])
	{
		n = str_to_env(args[i]);
		pe = previous_already_exists(n, s->env);
		if (pe)
		{
			sub = n->next;
			pe->next = sub;
			free_tenv(n);
		}
		i++;
	}
	s->env = r;
	env_to_pipe(s->env, s->p_env);
	exit(EXIT_SUCCESS);
}
