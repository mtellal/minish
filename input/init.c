/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:34:24 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/25 17:54:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_sinput(t_input *s, int argc, char **argv, char **env)
{
	s->argc = argc;
	s->argv = argv;
	s->env = env;
	s->input = NULL;
}
