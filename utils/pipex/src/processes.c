/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:14:32 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/11 10:33:38 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_pip *s)
{
	if (s->option == OUTPUT || s->option == APPEND)
		close(s->fdo);
	if (s->option == INPUT || s->option == HEREDOC)
		close(s->fdi);
	if (s->option == NONE)
	{
		close(s->fdi);
		close(s->fdo);
	}
}

void	close_all_pipes(t_pip *s)
{
	int	i;

	i = 0;
	while (i < s->nb_cmd - 1)
	{
		close(s->pipe[i][0]);
		close(s->pipe[i][1]);
		free(s->pipe[i]);
		i++;
	}
	free(s->pipe);
	close_fd(s);
}

void	ft_exe(t_pip *s, int i)
{
	close_all_pipes(s);
	if (execve(s->cmd[i], s->arg[i], s->data.env) == -1)
	{
		write(2, "Error: command not found: ", 26);
		write(2, s->cmd[i], ft_strlen(s->cmd[i]));
		err("\nError", 1);
	}
}

void	process(t_pip *s, int i, int nbp)
{
	if (i == (nbp - 1))
	{
		ft_dup2(s->fdi, 0);
		ft_dup2(s->pipe[(nbp - 1) - i][1], 1);
		ft_exe(s, 0);
	}
	if (i == nbp)
	{
		if (s->nb_pipes != 0)
			ft_dup2(s->pipe[i - 1][0], 0);
		else
			ft_dup2(s->fdi, 0);
		ft_dup2(s->fdo, 1);
		ft_exe(s, i);
	}
	else
	{
		ft_dup2(s->pipe[i][0], 0);
		ft_dup2(s->pipe[i + 1][1], 1);
		ft_exe(s, i + 1);
	}
}

/*
 * 	unlink here_doc
 *	wait(NULL); pour les enfants ??
 *
 *	!!!!!!!!!!!!! verify wait(NULL) + tests !!!!!!!!!!!!!!!!!
 */

void	processes(t_pip *s)
{
	int		i;
	int		nb_pipes;
	pid_t	f;

	i = 0;
	nb_pipes = s->nb_pipes;
	while (i < nb_pipes)
	{
		f = fork();
		if (f == -1)
			err("error forking", 1);
		if (f == 0)
			process(s, i, nb_pipes);
		i++;
	}
	wait(NULL);
	if (s->hd)
		unlink(".here_doc");
	process(s, nb_pipes, nb_pipes);
}
