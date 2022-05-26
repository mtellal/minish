/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:19:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/26 21:46:03 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    open_data(t_utils *data, char *r)
{
         if (!ft_strcmp(r, "<"))
                open_n_close(data, O_RDONLY, 0, r);
        if (!ft_strcmp(r, ">"))
                open_n_close(data, O_CREAT | O_RDWR | O_TRUNC, 0666, r);
        if (!ft_strcmp(r, ">>"))
                open_n_close(data, O_CREAT | O_RDWR | O_APPEND, 0666, r);
        if (!ft_strcmp(r, "<<"))
                open_n_close_hd(data);
}

void    open_n_close(t_utils *data, int flags, mode_t mode, char *r)
{
        if (*r == '<' && data->cmd && data->cmd->fdi > 2)
                close(data->cmd->fdi);
        if (*r == '>' && data->cmd && data->cmd->fdo > 2)
                close(data->cmd->fdo);
        if (ft_open(&data->file, data->tab[0], flags, mode) == -1)
        {
                ft_putstr_fd("err input file \n", 2);
                exit(0);
        }
}

void    open_n_close_hd(t_utils *data)
{
        char    *buffer;

        if (data->cmd && data->cmd->fdi > 2)
                close(data->cmd->fdi);
        if (ft_open(&data->file, ".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666) == -1)
        {
                ft_putstr_fd("err open heredoc\n", 2);
                exit(0);
        }
        while ((buffer = readline("heredoc> ")))
        {
                if (!ft_strcmp(buffer, data->tab[0]))
                {
                        free(buffer);
                        break ;
                }
                buffer = ft_strjoin_free(buffer, "\n", 1, 0);
                ft_putstr_fd(buffer, data->file);
                free(buffer);
        }
        close(data->file);
        if (ft_open(&data->file, ".heredoc", O_RDONLY, 0666) == -1)
        {
                ft_putstr_fd("err open .heredoc", 2);
                exit(0);
        }
}

