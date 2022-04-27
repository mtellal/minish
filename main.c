/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:38:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 16:26:46 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	// static declaration of structs
	t_input		i;

	if (argc == 1)
	{
		pipex(argc, argv, env);
		input(&i, argc, argv, env);
	}
	else
		ft_putstr_fd("Wrong number of arguments\n", 1);
	return (0);
}
