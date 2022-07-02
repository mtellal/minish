/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:35:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/30 10:20:02 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ctrl_d(t_input *s)
{
	ft_putstr_fd("\nexit\n", 1);
	free_all(s, 1);
	exit(EXIT_SUCCESS);
}

void	exec_sig_int(int n)
{
	if (n == SIGINT)
	{
		set_last_status(130);
		ft_putchar_fd('\n', 2);
	}
}

void    sig_int(int n)
{
        if (n == SIGINT)
        {
		set_last_status(130);
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int_hd(int n)
{
	if (n == SIGINT)
	{
		set_last_status(130);
		set_quit_hd(1);
		close(STDIN_FILENO);
		ft_putstr_fd("\n", 2);
	}
}

void	exec_sig_quit(int n)
{
	if (n == SIGQUIT)
	{
		if (get_last_pid())
			kill(get_last_pid(), n);
	}
}

void	init_exec_signals(void)
{
	signal(SIGINT, &exec_sig_int);
        signal(SIGQUIT, &exec_sig_quit);
}
