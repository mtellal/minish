/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:23:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/30 15:40:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	suivant l'id de la commande changer le add_back ou add_front ou add_index
 */

void    set_pipe(t_token *plist, t_token *nlist, t_input *s, int index)
{
        t_cmd   *pcmd;
        t_cmd   *ncmd;

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
                ncmd->fdi  = -2;
        if (pcmd && pcmd->fdo == 1)
                pcmd->fdo = -2;
        plist->next = nlist;
}

void	cmd_pipes(t_token *token, t_input *s)
{
	t_token	*list;
	t_token *plist;
	int	i_cmd;
	int	reset;

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
                                set_pipe(plist, list->next, s, i_cmd);
                                list = s->clist;
                                i_cmd = -1;
                                reset = 1;
				s->nb_pipes++;
			}
                }
                else
                        i_cmd++;
                if (!reset)
                {
                        plist = list;
                        list = list->next;
                }
        }
}
