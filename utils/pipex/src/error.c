/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:29:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/30 21:37:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_pip *s)
{
	close(s->fdo);
	if (s->hd)
		unlink(".here_doc");
	else
		close(s->fdi);
}

void	err(char *err, int eno)
{
	if (eno)
		perror(err);
	else
	{
		if (err && *err)
		{
			ft_putstr_fd(err, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	exit(0);
}

void	ft_dup2(int new, int old)
{
	if (dup2(new, old) == -1)
		err("Err dup", 1);
}

void	ft_pipe(int i, t_pip *s)
{
	int	j;

	j = 0;
	s->pipe = malloc(sizeof(int **) * i);
	while (j < i)
	{
		s->pipe[j] = malloc(sizeof(int) * 2);
		if (!s->pipe[j] || pipe(s->pipe[j]) == -1)
		{
			close_files(s);
			while (j > 0)
			{
				free(s->pipe[j]);
				j--;
			}
			err("Error pipe\nError", 1);
		}
		j++;
	}
}

void	free_s(t_pip *s, int pipe, int args, int cmd)
{
	if (pipe)
		close_all_pipes(s);
	if (args)
		free_args(s);
	if (cmd)
		free_cmd(s);
	exit(0);
}
