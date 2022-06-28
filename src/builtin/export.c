/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:31:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/28 16:23:13 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_env_var(char *args, t_input *s)
{
	t_env	*e;
	t_env	*n;

	n = str_to_env(args);
	e = var_exists(n->var, s->env);
	if (e)
	{
		e->content = ft_strdup(n->content);
		if (n->var)
			free(n->var);
		if (n->content)
			free(n->content);
		free(n);
	}
	else if (n)
		ft_lstadd_back_env(&s->env, n);
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
	t_env	*r;

	r = s->env;
	i = 1;
	if (args && !args[i])
		export_declare(s);
	while (args && args[i])
	{
		if (ft_str_valid(args[i]))
			set_env_var(args[i], s);
		i++;
	}
	s->env = r;
	return (return_status(EXIT_SUCCESS, s));
}
