/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:03:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/27 15:36:05 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char    *join_tab(char **tab, int j)
{
        char    *t;

        t = NULL;
        while (tab[j])
        {
                if (!t)
                        t = ft_strjoin_free(t, tab[j], 0, 0);
                else
                        t = ft_strjoin_free(t, tab[j], 1, 0);
                t = ft_strjoin_free(t, " ", 1, 0);
                j++;
        }
        free_tab(tab);
        return (t);
}

void    modify_redirection(t_utils *data, t_list *plist, t_list *nlist, char *rest_args, char *r)
{
        if (*r == '<')
                data->cmd->fdi = data->file;
        if (*r == '>')
                data->cmd->fdo = data->file;
        if (nlist)
                plist->next = nlist->next;
        else
                plist->next = nlist;
        if (rest_args)
                data->cmd->args = ft_strjoin_free(data->cmd->args, rest_args, 0, 1);
}

/*	SUREMENT OBSOLETES => FAIRE + DE TESTS POUR VERIFIER AUCUN PROBELEME
void    redir_n_cmd(t_input *s, t_utils *data, char *rest_args, int index, t_list *plist, t_list *nlist, char *r)
{
        //      < file cmd args   ||  | < file cmd args
        //      > file cmd args   ||  | > file cmd args

        if (*r == '<')
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args,index)));
        if (*r == '>')
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, index)));
        if (plist)
                plist->next = nlist;
        else
                s->clist = nlist;
        data->ntoken->c = rest_args;
}

void    cmd_n_redir(t_input *s, t_utils *data, char *rest_args, int index, t_list *plist, t_list *nlist, char *r)
{
        //      cmd < file args
        //      cmd > file args

        rest_args = ft_strjoin_free(data->ptoken->c, rest_args, 0, 1);
        if (*r == '<')
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args, index)));
        if (*r == '>')
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, index)));
        data->ptoken->c = rest_args;
        plist->next = nlist->next;
}
*/
