/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:31:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/07 21:20:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//	identifier valide = alnum ou '_'

t_env	*already_exists(t_env *n, t_env *env)
{
	t_env	*r;

	r = env;
	while (env)
	{
		if (!ft_strcmp(env->var, n->var))
			return (env);
		env = env->next;
	}
	env = r;
	return (NULL);
}

void	modify_content(t_env *e, t_env *n)
{
	e->content = ft_strdup(n->content);
	if (n->var)
		free(n->var);
	if (n->content)
		free(n->content);
	free(n);
}

void	export_declare(t_input *s)
{
	while (s->env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(s->env->var, 1);
		if (s->env->content && s->env->content[0])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(s->env->content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		s->env = s->env->next;
	}
}

void	ft_export(char **args, t_input *s)
{
	int		i;
	t_env	*n;
	t_env	*r;
	t_env	*e;

	r = s->env;
	i = 1;
	if (args && !args[i])
		export_declare(s);
	while (args && args[i])
	{
		if (ft_str_valid(args[i]))
		{
			n = str_to_env(args[i]);
			e = already_exists(n, s->env);
			if (!e)
				ft_lstadd_back_env(&s->env, n);
			else
				modify_content(e, n);
		}
		i++;
	}
	s->env = r;
	env_to_pipe(s->env, s->p_env);
	ft_putstr_fd("////////// export /////////\n", 2);
	exit(EXIT_SUCCESS);
}
