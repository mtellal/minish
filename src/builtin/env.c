/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:41:52 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/28 16:21:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_env(t_env *lenv, t_input *s)
{
	t_env	*env;

	env = lenv;
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->content, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (return_status(EXIT_SUCCESS, s));
}
