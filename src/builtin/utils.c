/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:30:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 15:32:20 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	return_status(int status, t_input *s)
{
	if (s->nb_cmd > 1)
		exit(status);
	else
		s->lstatus = status;
}
