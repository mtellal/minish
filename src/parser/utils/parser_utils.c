/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:47:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 15:33:16 by mtellal          ###   ########.fr       */
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

void	progress_list_space(t_token **list, t_token **plist, t_token **nlist)
{
	*plist = *list;
	*list = (*list)->next;
	if (*list)
		*nlist = (*list)->next;
}

void	clear_space(t_token *list, t_input *s)
{
	t_token	*plist;
	t_token	*nlist;
	t_token	*token;
	t_token	*r;

	plist = NULL;
	r = list;
	while (list)
	{
		token = NULL;
		if (list->type == ALPHANUM)
		{
			if (only_space(list->c))
			{
				token = list;
				if (!plist)
					s->clist = list->next;
				else
					plist->next = list->next;
			}
		}
		progress_list_space(&list, &plist, &nlist);
		free_token(&token);
	}
	list = r;
}
