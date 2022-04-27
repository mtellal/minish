/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 13:49:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	input(t_input *si, int argc, char **argv, char **env)
{
	init_sinput(si, argc, argv, env);
	getInput(si);
	
	return (0);
}
