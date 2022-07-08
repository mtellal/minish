/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:23:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 11:21:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	*last_status(void)
{
	static int	last_s = 0;

	return (&last_s);
}

int	get_last_status(void)
{
	return (*last_status());
}

void	set_last_status(int status)
{
	*last_status() = status;
}

void	return_status(int status, t_input *s)
{
	if (s->nb_cmd > 1)
	{
		free_all(s, 1);
		exit(status);
	}
	else
		set_last_status(status);
}
