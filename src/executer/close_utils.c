/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:16:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/08 15:36:00 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_fds(t_cmd *cmd)
{
	if (cmd->fdi > 2 && dup2(cmd->fdi, 0) == -1)
	{
		ft_putstr_fd("\nerr dup2 ", 2);
		perror("");
		exit(EXIT_FAILURE);
	}
	if (cmd->fdo > 2 && dup2(cmd->fdo, 1) == -1)
	{
		ft_putstr_fd("\nerr dup2 ", 2);
		perror("");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(t_input *s)
{
	t_cmd	*cmd;

	cmd = s->cmd;
	while (cmd)
	{
		if (cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd->fdo > 2)
			close(cmd->fdo);
		cmd = cmd->next;
	}
}

void	close_pipes(int **pipes, int index)
{
	int	i;

	i = 0;
	while (pipes && pipes[i] && i < index)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	restore_fds(t_coor fds)
{
	dup2(fds.i, STDIN_FILENO);
	dup2(fds.j, STDOUT_FILENO);
}
