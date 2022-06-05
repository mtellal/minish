/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:41:52 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 09:41:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->content, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	exit(EXIT_SUCCESS);
}
