/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:16:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 17:05:49 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    set_fds(t_cmd *cmd)
{
        if (cmd->fdi > 2 && dup2(cmd->fdi, 0) == -1)
        {
                ft_putstr_fd("\nerr dup2 ", 2);
                ft_putstr_fd(cmd->args, 2);
                ft_putstr_fd(" ", 2);
                ft_putnbr_fd(cmd->fdi, 2);
                ft_putstr_fd("\n", 2);
                perror("");
                exit(0);
        }
        if (cmd->fdo > 2 && dup2(cmd->fdo, 1) == -1)
        {
                ft_putstr_fd("\nerr dup2 ", 2);
                ft_putstr_fd(cmd->args, 2);
                ft_putstr_fd(" ", 2);
                ft_putnbr_fd(cmd->fdo, 2);
                ft_putstr_fd("\n", 2);
                perror("");
                exit(0);
        }
}

void    close_fds(t_input *s)
{
        t_cmd   *cmd;

        cmd = s->cmd_list;
        while (cmd)
        {
                if (cmd->fdi > 2)
                        close(cmd->fdi);
                if (cmd->fdo > 2)
                        close(cmd->fdo);
                cmd = cmd->next;
        }
}

void	close_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes && pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
