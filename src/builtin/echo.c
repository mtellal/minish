/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:59:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/29 18:09:48 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	echo(char *args, char *n_args)
{
	if (args && args[0] == '$')
	{
		if (!ft_strcmp(args, "$?"))
			ft_putnbr_fd(get_last_status(), STDIN_FILENO);
	}
	else
		ft_putstr_fd(args, 1);
	if (n_args)
		ft_putstr_fd(" ", 1);
}

int	print_args(char *args)
{
	int	i;

	 if (!ft_strncmp(args, "-n", 2))
	 {
		 i = 2;
		 while (args[i] && args[i] == 'n')
		 	i++;
		 if (!args[i])
			 return (0);
		 else
			 return (1);
	 }
	 else
		 return (1);
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
		if (print_args(args[i]))
			echo(args[i], args[i + 1]);
		i++;
	}
	if (sl)
		ft_putstr_fd("\n", 1);
	return (return_status(EXIT_SUCCESS, s));
}
