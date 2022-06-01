/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:38:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 21:06:33 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int main(int argc, char **argv, char **env)
{
	t_input		s;

	if (argc == 1)
	{
		launch(&s, argc, argv, env);
	}
	else
		ft_putstr_fd("Wrong number of arguments\n", 1);
	return (0);
}
