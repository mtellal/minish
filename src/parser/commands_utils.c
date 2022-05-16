/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/16 16:28:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*option(enum s_options opt)
{
	if (opt == NOFILES)
		return ("NOFILES");
	if (opt == INPUT)
		return ("INPUT");
	if (opt == OUTPUT)
		return ("OUTPUT");
	if (opt == APPEND)
		return ("APPEND");
	if (opt == HEREDOC)
		return ("HEREDOC");
	return ("NONE");
}

void	clear_cmd_list(t_list *list, t_input *s)
{
	t_list	*l;
	t_cmd	*cmd;

	l = list;
	while (list)
	{
		cmd = list->content;
		if (cmd->fdi)
			free(cmd->fdi);
		if (cmd->fdo)
			free(cmd->fdo);
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
		printf("%i   |   FDI:'%s'   |   FDO:'%s'	|   ARGS:'%s'  |  OPTION:%s \n", i, cmd->fdi, cmd->fdo, cmd->args, option(cmd->option));
		list = list->next;
		i++;
	}
}
