/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:59:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 15:24:19 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	echo(char *args, char *n_args, t_input *s)
{
	if (args && args[0] == '$')
	{
		if (!ft_strcmp(args, "$?"))
			ft_putnbr_fd(s->lstatus, 1);
	}
	else
		ft_putstr_fd(args, 1);
	if (n_args)
		ft_putstr_fd(" ", 1);
}

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
		echo(args[i], args[i + 1], s);
		i++;
	}
	if (sl)
		ft_putstr_fd("\n", 1);
	return (return_status(EXIT_SUCCESS, s));
}
