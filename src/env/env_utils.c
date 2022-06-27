/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:54:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 11:42:20 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	return pointer to value of a var if she exists
 */

t_env   *var_exists(char *var, t_env *lenv)
{
        t_env   *env;

        env = lenv;
        while (env)
        {
                if (!ft_strcmp(env->var, var))
                        return (env);
                env = env->next;
        }
        return (NULL);
}

char	*get_var_value(char *var, t_input *s)
{
	t_env	*e;

	e = var_exists(var, s->env);
	if (e)
		return (e->content);
	return (NULL);	
}

void	set_var_value(char *var, char *value, t_input *s)
{
	t_env	*e;

	e = var_exists(var, s->env);
	if (e)
	{
		free(e->content);
		e->content = ft_strdup(value);
	}
}

void	free_env(t_input *s)
{
	t_env	*sub;

	sub = NULL;
	while (s->env)
	{
		if (s->env->var)
			free(s->env->var);
		if (s->env->content)
			free(s->env->content);
		sub = s->env->next;
		free(s->env);
		s->env = sub;
	}
	s->env = NULL;
}

char	**env_to_tab(t_env *list)
{
	t_env	*env;
	char	**tab;
	char	*s;

	env = list;
	tab = NULL;
	s = NULL;
	while (env)
	{
		s = ft_strdup(env->var);
		s = ft_strjoin(s, "=");
		s = ft_strjoin(s, env->content);
		tab = add_tab(tab, s, 1, 0);
		s = NULL;
		env = env->next;
	}
	return (tab);
}

t_env	*ft_lstlast_env(t_input *s)
{
	t_env	*r;
	t_env	*l;

	r = s->env;
	while (s->env->next)
		s->env = s->env->next;
	l = s->env;
	s->env = r;
	return (l);
}
