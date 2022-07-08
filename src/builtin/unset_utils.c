/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:12:14 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 13:17:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	lst_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	free_tenv(t_env *e)
{
	if (!e)
		return ;
	if (e->var)
		free(e->var);
	if (e->content)
		free(e->content);
	free(e);
}

int	msg_err_unset(char *tab)
{
	ft_putstr_fd("error: unset: << ", 2);
	ft_putstr_fd(tab, 2);
	ft_putstr_fd(" >> : invalid id\n", 2);
	return (-1);
}
