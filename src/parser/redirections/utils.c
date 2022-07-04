/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:25:50 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 18:28:31 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    err_msg_redirection(char *err)
{
        if (err)
        {
                ft_putstr_fd("error: ", 2);
                ft_putstr_fd(err, 2);
                ft_putstr_fd("\n", 2);
        }
}

//      useful when sig quit is send in heredoc prompt

void    reset_stdin(void)
{
        int     fd;

        fd = dup(STDIN_FILENO);
        if (get_quit_hd())
                dup2(fd, STDIN_FILENO);
        else
                close(fd);
}


