/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:12:38 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 17:20:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	**free_pipes_index(int **p, int i)
{
	i--;
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	ft_putstr_fd("Error in creating pipes\n", 2);
	return (NULL);
}

int	**create_pipes(int nb_pipes)
{
	int	**p;
	int	i;

	i = 0;
	if (!nb_pipes)
		return (NULL);
	p = malloc(sizeof(int *) * (nb_pipes + 1));
	while (i < nb_pipes)
		p[i++] = NULL;
	i = 0;
	while (i < nb_pipes)
	{
		p[i] = ft_calloc(2, sizeof(int));
		if (!p[i] || pipe(p[i]) == -1)
			return (free_pipes_index(p, i));
		i++;
	}
	p[i] = NULL;
	return (p);
}

void	pipes(int j, int *i_p, t_input *s)
{
	t_cmd	*cmd;

	cmd = cmd_index(s->cmd, j);
	if (cmd && cmd->fdi == -2)
	{
		cmd->fdi = s->pipes[*i_p][0];
	}
	else if (*i_p >= 0 && s->pipes[*i_p])
		close(s->pipes[*i_p][0]);
	(*i_p)++;
	if (cmd && cmd->fdo == -2)
	{
		cmd->fdo = s->pipes[*i_p][1];
	}
	else if (*i_p >= 0 && s->pipes[*i_p])
		close(s->pipes[*i_p][1]);
}

int	pipe_needed(t_cmd *lcmd)
{
	t_cmd	*cmd;

	cmd = lcmd;
	while (cmd)
	{
		if (cmd && cmd->fdi == -2)
			return (1);
		if (cmd && cmd->fdo == -2)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	set_pipes(t_cmd *list, t_input *s)
{
	int		len;
	int		j;
	int		i_p;

	if (!pipe_needed(list))
		return ;
	len = ft_lstsize_cmd(list);
	j = 0;
	i_p = -1;
	s->pipes = create_pipes(s->nb_pipes);
	if (!s->pipes)
		return ;
	while (j < len)
	{
		pipes(j, &i_p, s);
		j++;
	}
}
