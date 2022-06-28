/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:25:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/28 17:58:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//	verifier si d'autres singaux a prendre en compte 
//	ou d'autres options pour &status

static	int	*last_pid(void)
{
	static int	pid = 0;

	return (&pid);
}

int	get_last_pid(void)
{
	return (*last_pid());
}

void	set_last_pid(int pid)
{
	*last_pid() = pid;	
}

void	wait_all(t_input *s, pid_t *f)
{
	int	i;
	int	status;
	int	signal;

	i = 0;
	while (i < s->nb_cmd)
	{
		waitpid(f[i], &status, 0);
		if (WIFEXITED(status))
			set_last_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			if (signal == SIGQUIT)
				ft_putstr_fd("Quit from keyboard\n", 2);
			else
				set_last_status(128 + WTERMSIG(status));
		}
		i++;
	}
	free(f);
}
