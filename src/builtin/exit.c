/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:17:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 17:09:09 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_exit(t_cmd *cmd, t_input *s)
{
	if (cmd && cmd->cmd_args && ft_strlen_tab(cmd->cmd_args) >= 2)
	{
		ft_putstr_fd("error: exit: ", 2);
		ft_putstr_fd(cmd->cmd_args[1], 2);
		ft_putstr_fd(": numeric argument not needed\n", 2);
		return (return_status(2, s));
	}
	else
	{
		free_all(s, 1);
		ft_putstr_fd("exit\n", 1);
		return (return_status(EXIT_SUCCESS, s));
	}
}
