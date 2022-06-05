/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:12:38 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/04 17:36:29 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	**create_pipes(t_input *s)
{
	int	**p;
	int	i;

	i = 0;
	if (!s->nb_pipes)
		return (NULL);
	p = ft_calloc(s->nb_pipes, sizeof(int *));
	while (i < s->nb_pipes)
	{
		p[i] = ft_calloc(2, sizeof(int));
		if (!p[i] || pipe(p[i]) == -1)
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
		i++;
	}
	return (p);
}

void	pipes(int *j, int *i, int *iid, t_input *s)
{
	t_cmd	*pcmd;
	t_cmd	*cmd;

	cmd = cmd_index(s->cmd_list, *j);
	pcmd = NULL;
	if (*j > 0)
		pcmd = cmd_index(s->cmd_list, *j - 1);
	if (cmd && cmd->fdi == -2)
	{
		if (pcmd && pcmd->fdo != s->pipes[*iid][1])
			close(s->pipes[*iid][1]);
		cmd->fdi = s->pipes[*iid][0];
		*i += 1;
		if (*i % 2 == 0)
			*iid += 1;
	}
	if (cmd && cmd->fdo == -2)
	{
		*i += 1;
		if (*i % 2 == 0)
                        *iid += 1;
		cmd->fdo = s->pipes[*iid][1];
	}
}

void	set_pipes(t_cmd *list, t_input *s)
{
	int		len;
	int		j;
	int		i;
	int		iid;

	len = ft_lstsize_cmd(list);
	j = 0;
	i = 0;
	iid = 0;
	s->pipes = create_pipes(s);
	if (!s->pipes)
		return ;
	while (j < len)
	{
		pipes(&j, &i, &iid, s);
		j++;
	}
}
