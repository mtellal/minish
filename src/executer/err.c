/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:39:57 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/07 17:48:12 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	err_msg_cmd(char *cmd)
{
	ft_putstr_fd("Error command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	err_cmd(t_cmd *cmd, t_input *s, int msg)
{
	if (msg)
		err_msg_cmd(cmd->cmd_args[0]);
	close_pipes(s->pipes);
	exit(EXIT_FAILURE);
}

