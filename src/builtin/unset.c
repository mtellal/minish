/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/30 17:04:56 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    ft_unset(t_input *s, char *str)
{
    t_env   *tmp;
    t_env   *to_delete;
    unsigned int     len;

    len = ft_strlen(str);
    //faire une fonction qui free la premiere node
    if (ft_strlen(s->env->var) == len && ft_memcmp(s->env->var, str, len) == 0)
        s->env = s->env->next;
    tmp = s->env;
    while (tmp && tmp->next)
    {
        if (ft_strlen(tmp->next->var) == len && ft_memcmp(tmp->next->var, str, len) == 0)
        {
            printf("happens\n");
            if (tmp->next != NULL)
            {
                printf("to_delete=%s\n", tmp->next->var);
                to_delete = tmp->next;
                tmp->next = tmp->next->next;
                free(to_delete->var);
                free(to_delete->content);
                free(to_delete);
            }
        }
        tmp = tmp->next;
    }
}
