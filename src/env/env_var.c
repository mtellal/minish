/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:11:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 13:27:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_env	*var_exists(char *var, t_env *lenv)
{
	t_env	*env;

	env = lenv;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			return (env);
		env = env->next;
	}
	return (NULL);
}
