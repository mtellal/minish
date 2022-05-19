/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:12:38 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/18 17:57:29 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     **create_pipes(t_input *s)
{
        int     **p;
        int     i;

        i = 0;
        if (!s->nb_pipes)
                return (NULL);
        p = ft_calloc(s->nb_pipes, sizeof(int*));
        while (i < s->nb_pipes)
        {
                p[i] = ft_calloc(2, sizeof(int));
                if (!p[i] || pipe(p[i]) == -1)
                {
                        i--;
                        while (i >= 0)
                        {
                                free(p[i]);
                                i--;
                        }
                        ft_putstr_fd("Error in creating pipes\n", 2);
                        return (NULL);
                }
                i++;
        }
        return (p);
}

void    set_pipes(t_list *list, t_input *s)
{
        t_cmd   *cmd;
        int     i;
        int     len;
        int     j;

        len = ft_lstsize(list);
        j = 0;
        i = 0;
        s->pipes = create_pipes(s);
        if (!s->pipes)
                return ;
        while (j < len)
        {
                cmd = cmd_index(list, j);
                if (cmd && cmd->fdi == -2)
                {
                        cmd->fdi = s->pipes[i][0];
                        i++;
                }
                if (cmd && cmd->fdo == -2)
                        cmd->fdo = s->pipes[i][1];
                j++;
        }

}

