/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:35:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/21 16:05:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ctrl_d(t_input *s)
{
	free_env(s);
	ft_putstr_fd("\nexit\n", 1);
	exit(EXIT_SUCCESS);
}

void	redisplay(int n)
{
	if (n == SIGINT)
		ft_putchar_fd('\n', 1);
}

void    sig_int(int n)
{
        if (n == SIGINT)
        {
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
