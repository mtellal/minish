/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:23:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 09:44:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	suivant l'id de la commande changer le add_back ou add_front ou add_index
 */

void	set_pipe(t_token *plist, t_token *nlist, t_input *s, int index)
{
	t_cmd	*pcmd;
	t_cmd	*ncmd;

	pcmd = NULL;
	ncmd = NULL;
	if (s->cmd)
	{
		pcmd = cmd_index(s->cmd, index);
		ncmd = cmd_index(s->cmd, index + 1);
	}
	if (!pcmd)
	{
		pcmd = cmd(0, -2, plist->c, index);
		ft_lstaddb_cmd(&s->cmd, pcmd);
	}
	if (!ncmd)
	{
		ncmd = cmd (-2, 1, nlist->c, index + 1);
		ft_lstaddb_cmd(&s->cmd, ncmd);
	}
	if (ncmd && ncmd->fdi == 0)
		ncmd->fdi = -2;
	if (pcmd && pcmd->fdo == 1)
		pcmd->fdo = -2;
	plist->next = nlist;
}

void	set_list_plist(t_token **plist, t_token **list, int reset)
{
	if (!reset)
	{
		*plist = *list;
		*list = (*list)->next;
	}
}

void	pipe_match(t_token *plist, t_token **list, int *i_cmd, t_input *s)
{
	set_pipe(plist, (*list)->next, s, *i_cmd);
	free_token(list);
	*list = s->clist;
	*i_cmd = -1;
	s->nb_pipes++;
}

void	cmd_pipes(t_token *token, t_input *s)
{
	int		i_cmd;
	int		reset;
	t_token	*list;
	t_token	*plist;

	i_cmd = -1;
	reset = 0;
	list = token;
	plist = NULL;
	while (list)
	{
		reset = 0;
		if (list->type == SEPARATOR)
		{
			if (*list->c == '|')
			{
				pipe_match(plist, &list, &i_cmd, s);
				reset = 1;
			}
		}
		else
			i_cmd++;
		set_list_plist(&plist, &list, reset);
	}
}
