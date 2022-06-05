/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/03 11:02:43 by mtellal          ###   ########.fr       */
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
		if ((*cmd)->fdi > 2)
			close((*cmd)->fdi);
		if ((*cmd)->fdo > 2)
			close((*cmd)->fdo);
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
		printf("id: %i   |   FDI:'%i'   |   FDO:'%i'	|   ARGS:' %s '  | cmd:' %s ' | cmd_args:' %s '\n", cmd->id, cmd->fdi, cmd->fdo, cmd->args, cmd->cmd, tab_to_s(cmd->cmd_args, 0));
		cmd = cmd->next;
		i++;
	}	
}
