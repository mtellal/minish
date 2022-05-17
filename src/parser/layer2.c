/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:23:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/17 21:34:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    cmd_pipe(t_list *plist, t_list *nlist, t_input *s, int index)
{
        t_cmd   *pcmd;
        t_cmd   *ncmd;
        t_token *ptoken;
        t_token *ntoken;

        ptoken = plist->content;
        ntoken = nlist->content;
        pcmd = NULL;
        ncmd = NULL;
        if (s->cmd_list)
        {
                pcmd = list_index(s->cmd_list, index)->content;
                if (ft_lstsize(s->cmd_list) > index + 1)
                        ncmd = list_index(s->cmd_list, index + 1)->content;
        }
        if (!pcmd)
        {
                pcmd = cmd(0, -2, ptoken->c, NOFILES, index);
                ft_lstadd_back(&s->cmd_list, ft_lstnew(pcmd));
        }
        if (!ncmd)
        {
                ncmd = cmd (-2, 1, ntoken->c, NOFILES, index + 1);
                ft_lstadd_back(&s->cmd_list, ft_lstnew(ncmd));
        }
        if (ncmd && ncmd->fdi == 0)
                ncmd->fdi  = -2;
        if (pcmd && pcmd->fdo == 1)
                pcmd->fdo = -2;
        plist->next = nlist;
}

void	layer2(t_list *list, t_input *s)
{
	t_token	*token;
	t_list *plist;
	int	i_cmd;
	int	reset;

	i_cmd = -1;
        reset = 0;
	if (!list)
		return ;
	plist = NULL;
        while (list)
        {
                reset = 0;
                token = list->content;
                if (token->type == SEPARATOR)
                {
                        if (*token->c == '|')
                        {
                                cmd_pipe(plist, list->next, s, i_cmd);
                                list = s->clist;
                                i_cmd = -1;
                                reset = 1;
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
        ft_putstr_fd("///////////////////////////////\n\n", 2);
        show_command_table(s);
        //show_cmd_list(s->cmd_list);
}
