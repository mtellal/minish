/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:54:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/30 15:55:04 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	free_env(t_input *s)
{
	t_env	*sub;

	while (s->env)
	{
		if (s->env->var)
			free(s->env->var);
		if (s->env->content)
			free(s->env->content);
		sub = s->env;
		s->env = s->env->next;
		free(sub);
	}
	s->env = NULL;
}

char	**env_to_tab(t_env *env)
{
	t_env	*r;
	char	**tab;
	char	*s;

	r = env;
	tab = NULL;
	s = NULL;
	while (env)
	{
		s = ft_strdup(env->var);
		s = ft_strjoin_free(s, "=", 1, 0);
		s = ft_strjoin_free(s, env->content, 1, 1);
		tab = add_tab(tab, s, 1);
		s = NULL;
		env = env->next;
	}
	env = r;
	return (tab);
}

void    print_tab_env(t_env *env)
{
	char	**tab;
	int i;

	i = 0;
	tab = env_to_tab(env);
	ft_putstr_fd("////////////////// env to tab //////////////\n", 2);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
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
