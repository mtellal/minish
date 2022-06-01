/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:03:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 22:18:18 by mtellal          ###   ########.fr       */
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

