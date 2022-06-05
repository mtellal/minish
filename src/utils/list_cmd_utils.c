/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:03 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/03 13:51:37 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_lstsize_cmd(t_cmd *list)
{
	int	i;
	t_cmd	*r;

	i = 0;
	if (!list)
		return (0);
	r = list;
	while (list)
	{
		list = list->next;
		i++;
	}
	list = r;
	return (i);
}


void    free_cmd(t_cmd *cmd)
{
        if (!cmd)
                return ;
        if (cmd->args)
                free(cmd->args);
        free(cmd);
}


void    ft_lstaddb_cmd(t_cmd **lst, t_cmd *n)
{
        t_cmd *r;

        if (!n)
                return ;
        if (!lst || !*lst)
                *lst = n;
        else
        {
                r = *lst;
                while ((*lst)->next)
                        *lst = (*lst)->next;
                (*lst)->next = n;
                *lst = r;
        }
}

void    ft_lstclear_cmd(t_cmd **list)
{
        t_cmd *cmd;

        while (*list)
        {
                cmd = *list;
                *list = (*list)->next;
                free_cmd(cmd);
        }
        *list = NULL;
}

t_cmd *list_index_cmd(t_cmd *list, int l)
{
        int     i;

        i = 0;
        if (!list || l < 0)
                return (NULL);
        while (list && i < l)
        {
                list = list->next;
                i++;
        }
        return (list);
}
