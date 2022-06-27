/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:33:41 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/25 20:28:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    expander(t_cmd *lcmd, t_input *s)
{
        t_cmd   *cmd;

        cmd = lcmd;
        while (cmd)
        {
		if (cmd->args)
		{
                	if (*cmd->args)
                        	cmd->args = var_env(cmd->args, s);
                	else
				cmd->args = NULL;
		}
		cmd = cmd->next;
        }
}
