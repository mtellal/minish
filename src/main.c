/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:38:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 09:34:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	main(int argc, char **argv, char **env)
{
	t_input		s;

	(void)argv;
	if (argc == 1)
	{
		init(&s, argc, env);
		launch_minishell(&s);
	}
	else
		ft_putstr_fd("Wrong number of arguments\n", 1);
	return (0);
}
