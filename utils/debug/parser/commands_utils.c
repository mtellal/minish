/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 16:36:18 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	clear_cmd_list(t_list *list, t_input *s)
{
	t_list	*l;
	t_cmd	*cmd;

	l = list;
	while (list)
	{
		cmd = list->content;
		if (cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd->fdo > 2)
			close(cmd->fdo);
		if (cmd->args)
			free(cmd->args);
		free(cmd);
		l = list;
		list = list->next;
		free(l);
	}
	s->cmd_list = NULL;
}

void	show_cmd_list(t_list *list)
{
	int	i;
	t_cmd *cmd;

	i = 0;
	while (list)
	{
		cmd = list->content;
		printf("id: %i   |   FDI:'%i'   |   FDO:'%i'	|   ARGS:' %s '  | cmd:' %s ' \n", cmd->id, cmd->fdi, cmd->fdo, cmd->args, cmd->cmd);
		list = list->next;
		i++;
	}
}
