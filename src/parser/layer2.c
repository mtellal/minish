/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:23:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/17 14:49:13 by mtellal          ###   ########.fr       */
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
                pcmd = list_index(s->cmd_list, index - 1)->content;
                if (ft_lstsize(s->cmd_list) > index + 1)
                        ncmd = list_index(s->cmd_list, index)->content;
        }
        if (!pcmd)
        {
                pcmd = cmd(NULL, ft_strdup("pipe"), ptoken->c, NOFILES, index);
                ft_lstadd_back(&s->cmd_list, ft_lstnew(pcmd));
        }
        if (!ncmd)
        {
                ncmd = cmd (ft_strdup("pipe"), NULL, ntoken->c, NOFILES, index);
                ft_lstadd_back(&s->cmd_list, ft_lstnew(ncmd));
        }
        if (ncmd && !ncmd->fdi)
        {
                ncmd->fdi  = ft_strdup("pipe");
        }
        if (pcmd && !pcmd->fdo)
        {
                pcmd->fdo = ft_strdup("pipe");
        }
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
                                i_cmd = 0;
                                reset = 1;
                        }
                        /*if (*token->c == ';')
                        {
                                //      executer toutes les commands jusqu'q i conpris
                                //      exemple avec cmd sleep 2 cmd2; cmd 3
                                plist->next = list->next;
                        }*/
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
