/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:07:14 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 12:45:06 by mtellal          ###   ########.fr       */
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

void	print_tab_env(t_env *env)
{
	int		i;
	char	**tab;

	i = 0;
	tab = env_to_tab(env);
	ft_putstr_fd("////////////////// env to tab //////////////\n", 2);
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}

int	ft_lstenv_size(t_env *lenv)
{
	int		i;
	t_env	*env;

	i = 0;
	env = lenv;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
