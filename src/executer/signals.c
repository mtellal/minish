/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:35:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/07 20:37:33 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	exec_sig_int(int n)
{
	if (n == SIGINT)
	{
		set_last_status(130);
		ft_putchar_fd('\n', 2);
	}
}

void	sig_int(int n)
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
		set_quit_hd(1);
		set_last_status(130);
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	exec_sig_quit(int n)
{
	if (n == SIGQUIT)
	{
		if (get_last_pid())
			kill(get_last_pid(), n);
		set_last_status(131);
	}
}

void	init_exec_signals(void)
{
	signal(SIGINT, &exec_sig_int);
	signal(SIGQUIT, &exec_sig_quit);
}
