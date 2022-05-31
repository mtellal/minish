/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:35:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/31 19:22:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	redisplay(int n)
{
	if (n == SIGINT)
		ft_putchar_fd('\n', 1);
}

void    sig_int(int n)
{
        if (n == SIGINT)
        {
                ft_putstr_fd("\n", 1);
                ft_putstr_fd(PROMPT, 1);
        }
}

void    sig_quit(int n)
{
        if (n == SIGQUIT)
                exit(EXIT_SUCCESS);
}

