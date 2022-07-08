/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:54:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 15:48:50 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	return pointer to value of a var if she exists
 */

char	*get_var_value(char *var, t_input *s)
{
	t_env	*e;

	e = var_exists(var, s->env);
	if (e && e->content)
		return (ft_strdup(e->content));
	return (NULL);
}

void	set_var_value(char *var, char *value, t_input *s)
{
	t_env	*e;

	e = var_exists(var, s->env);
	if (e)
	{
		if (e->content)
			free(e->content);
		e->content = ft_strdup(value);
	}
}

void	free_env(t_env	**env)
{
	t_env	*sub;

	sub = NULL;
	while (*env)
	{
		if ((*env)->var)
			free((*env)->var);
		if ((*env)->content)
			free((*env)->content);
		sub = *env;
		*env = (*env)->next;
		free(sub);
	}
	*env = NULL;
}

char	**env_to_tab(t_env *list)
{
	int		i;
	t_env	*env;
	char	**tab;
	char	*s;

	env = list;
	tab = NULL;
	s = NULL;
	while (env)
	{
		i = 0;
		s = ft_strdup(env->var);
		if (env->equal == 1)
			s = ft_strjoin_free(s, "=", 1, 0);
		s = ft_strjoin_free(s, env->content, 1, 0);
		tab = add_tab(tab, s, 1, 1);
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
