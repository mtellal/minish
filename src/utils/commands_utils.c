/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 19:17:28 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	clear_cmd_list(t_cmd **cmd)
{
	t_cmd	*free_c;

	while (cmd && *cmd)
	{
		if ((*cmd)->args)
			free((*cmd)->args);
		if ((*cmd)->cmd_args)
			free_tab((*cmd)->cmd_args);
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->err_redir)
			free((*cmd)->err_redir);
		free_c = *cmd;
		*cmd = (*cmd)->next;
		free(free_c);
	}
	*cmd = NULL;
}

void	show_cmd_list(t_cmd *lcmd)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = lcmd;
	if (!cmd)
		ft_putstr_fd("no cmd list\n", 1);
	while (cmd)
	{
		cmd = cmd_index(lcmd, i);
		if (!cmd)
			break ;
		printf("id: %i   |   FDI:%i   |	 FDO:%i  ",
			cmd->id, cmd->fdi, cmd->fdo);
		printf("ARGS:' %s '  | cmd:' %s ' | cmd_args:' %s '\n",
			cmd->args, cmd->cmd, tab_to_s(cmd->cmd_args, 0));
		i++;
	}	
}
