/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:23:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 15:23:13 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    return_status(int status, t_input *s)
{
        if (s->nb_cmd > 1)
                exit(status);
        else
                s->lstatus = status;
}

