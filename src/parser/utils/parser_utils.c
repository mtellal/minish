/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/03 10:56:48 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_cmd	*cmd_index(t_cmd *list, int index)
{
	t_cmd	*cmd;

	cmd = list;
	if (!list || index < 0)
		return (NULL);
	while (cmd)
	{
		if (cmd->id == index)
			return (cmd);
		cmd = cmd->next;
	}
	return (NULL);
}

void	clear_space(t_token *list)
{
	t_token *plist;
	t_token	*nlist;
	t_token	*token;
	t_token *r;

	plist = NULL;
	r = list;
	while (list)
	{
		token = NULL;
		if (list->type == ALPHANUM)
		{
			if (only_space(list->c) && plist && nlist)
			{
				token = list;
				if (plist->type == SEPARATOR && nlist->type == SEPARATOR)
					plist->next = nlist;
			}
		}
		plist = list;
		list = list->next;
		if (list)
			nlist = list->next;
		free_token(&token);	
	}
	list = r;
}

