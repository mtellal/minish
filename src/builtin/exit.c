/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:17:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 17:07:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

int	set_status(char **args)
{
	int	status;
	int	i;

	i = 0;
	if (is_num(args[1]) || (ft_belong("-+", args[1][0]) && is_num(args[1] + 1)))
	{
		status = ft_atoi(args[1]);
		if (status < 0)
			status *= -255 - status;
		if (args[2])
		{
			status = -1;
			ft_putstr_fd("error: exit: error too many arguments\n", 2);
		}
	}
	else
	{
		ft_putstr_fd("error: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument needed\n", 2);
		status = 2;
	}
	return (status);
}

void	ft_exit(t_cmd *cmd, t_input *s)
{
	int	status;

	status = 0;
	if (cmd && cmd->cmd_args && ft_strlen_tab(cmd->cmd_args) >= 2)
		status = set_status(cmd->cmd_args);
	else
		status = EXIT_SUCCESS;
	if (status != -1)
	{
		free_all(s, 1);
		exit(status);
	}
	else
		set_last_status(EXIT_FAILURE);
}
