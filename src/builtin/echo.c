/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:59:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 10:05:16 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_echo(char **args, t_input *s)
{
	int	i;
	int	sl;

	i = 1;
	sl = 1;
	if (args && args[1] && !ft_strcmp(args[1], "-n"))
	{
		i++;
		sl = 0;
	}
	while (args && args[i])
	{
		if (args[i] && *args[i] == '$')
		{
			if (!ft_strcmp(args[i], "$?"))
				ft_putnbr_fd(s->lstatus, 1);
		}
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (sl)
		ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}
