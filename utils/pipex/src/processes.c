/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:14:32 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 17:48:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_pipes(t_pip *s)
{
	int	i;

	i = 0;
	while (i < s->data.argc - 4)
	{
		close(s->pipe[i][0]);
		close(s->pipe[i][1]);
		free(s->pipe[i]);
		i++;
	}
	free(s->pipe);
	close(s->fdi);
	close(s->fdo);
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
		ft_dup2(s, s->fdi, 0);
		ft_dup2(s, s->pipe[(nbp - 1) - i][1], 1);
		ft_exe(s, 0);
	}
	if (i == nbp)
	{
		ft_dup2(s, s->pipe[i - 1][0], 0);
		ft_dup2(s, s->fdo, 1);
		ft_exe(s, i);
	}
	else
	{
		ft_dup2(s, s->pipe[i][0], 0);
		ft_dup2(s, s->pipe[i + 1][1], 1);
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

	nb_pipes = s->data.argc - 4;
	i = 0;
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
	/*i = 0;
        while (i < nb_pipes - 1)
        {
                wait(NULL);
                i++;
        }*/
	process(s, nb_pipes, nb_pipes);
}
