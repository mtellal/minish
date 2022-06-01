/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:25:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 15:06:31 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//	verifier si d'autres singaux a prendre en compte ou d'autres options pour &status

void	wait_all(t_input *s, pid_t *f)
{
	int	i;
	int	status;

	i = 0;
	while (i < s->nb_cmd)
	{
		waitpid(f[i], &status, 0);
		if (WIFEXITED(status))
			s->lstatus = WEXITSTATUS(status);
		else
		{
			if (WIFSIGNALED(status))
				s->lstatus = WTERMSIG(status);
		}
		i++;
	}
	free(f);
}
