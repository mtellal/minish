/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:29:37 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 18:17:24 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static  int     *quit_hd(void)
{
        static int     hd = 0;

        return (&hd);
}

int     get_quit_hd(void)
{
        return (*quit_hd());
}

void    set_quit_hd(int n)
{
        *quit_hd() = n;
}

int     open_n_close_hd(t_utils *data)
{
        char    *buffer;
        int             flags;

        signal(SIGINT, &sig_int_hd);
        flags = O_CREAT | O_RDWR | O_TRUNC;
        if (data->cmd && data->cmd->fdi > 2)
                close(data->cmd->fdi);
        if (ft_open(&data->file, ".heredoc", flags, 0666) == -1)
                return (-1);
        while (1)
        {
		buffer = readline("heredoc> ");
                if (get_quit_hd() || !buffer || !ft_strcmp(buffer, data->tab[0]))
                {
			if (!buffer)
                                ft_putstr_fd("\n", 1);
			break ;
                }
                buffer = ft_strjoin_free(buffer, "\n", 1, 0);
                ft_putstr_fd(buffer, data->file);
                free(buffer);
        }
	close(data->file);
        if (ft_open(&data->file, ".heredoc", O_RDONLY, 0666) == -1)
                return (-1);
        return (0);
}

