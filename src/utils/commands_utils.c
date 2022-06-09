/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/06 21:01:30 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	clear_cmd_list(t_cmd **cmd)
{
	t_cmd	*free_c;

	while (*cmd)
	{
		if ((*cmd)->args)
			free((*cmd)->args);
		if ((*cmd)->cmd_args)
			free_tab((*cmd)->cmd_args);
		free_c = *cmd;
		*cmd = (*cmd)->next;
		free(free_c);
	}
	*cmd = NULL;
}

void	show_cmd_list(t_cmd *lcmd)
{
	int	i;
	t_cmd *cmd;

	i = 0;
	cmd = lcmd;
	while (cmd)
	{
		cmd = cmd_index(lcmd, i);
		printf("id: %i   |   FDI:%i   |   FDO:%i  ", cmd->id, cmd->fdi, cmd->fdo);
		printf("ARGS:' %s '  | cmd:' %s ' | cmd_args:' %s '\n", cmd->args, cmd->cmd, tab_to_s(cmd->cmd_args, 0));
		cmd = cmd->next;
		i++;
	}	
}
