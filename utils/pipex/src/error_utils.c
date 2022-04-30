/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:06:39 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/30 19:22:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dup(int fd)
{
	int	f;

	f = dup(fd);
	if (f == -1)
		err("Err dup", 1);
	return (f);
}

int	ft_open(int *fd, char *file, int flags, mode_t mode)
{
	*fd = open(file, flags, mode);
	if (*fd == -1)
		return (-1);
	return (0);
}

void	free_args(t_pip *s)
{
	int		i;
	int		j;

	i = 0;
	while (i < (s->data.argc - 3))
	{
		j = 0;
		while (s->arg[i][j] && *(s->arg[i][j]))
		{
			free(s->arg[i][j]);
			j++;
		}
		free(s->arg[i]);
		i++;
	}
	free(s->arg);
}

void	free_cmd(t_pip *s)
{
	int	i;

	i = 0;
	while (i < (s->data.argc - 3) && s->cmd[i] && *s->cmd[i])
	{
		free(s->cmd[i]);
		i++;
	}
	free(s->cmd);
}
