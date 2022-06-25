/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:32:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/24 16:33:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	show_env(t_env	*env)
{
	t_env	*r;

	r = env;
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd(env->var, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(env->content, 2);
		ft_putstr_fd("\n", 2);
		env = env->next;
	}
	env = r;
}

void    print_tab_env(t_env *env)
{
        char    **tab;
        int             i;

        i = 0;
        tab = env_to_tab(env);
        ft_putstr_fd("////////////////// env to tab //////////////\n", 2);
        while (tab[i])
        {
                printf("%s\n", tab[i]);
                i++;
        }
}

