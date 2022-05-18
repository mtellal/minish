/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/18 10:02:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_fds(int fdi, int fdo)
{
	if (dup2(fdi, 0) == -1)
	{
		ft_putstr_fd("err dup2\n", 2);
		exit(0);
	}
	if (dup2(fdo, 1) == -1)
	{
		ft_putstr_fd("err dup2\n", 2);
		exit(0);
	}
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->fdi > 2)
		close(cmd->fdi);
	if (cmd->fdo > 2)
		close(cmd->fdo);
}

void	execute(t_cmd *cmd, char **args, t_input *s)
{
	pid_t	p;

	p = fork();
	if (p == 0)
	{
		set_fds(cmd->fdi, cmd->fdo);
		close_fds(cmd);
		if (execve(cmd->p_cmd, args, s->env) == -1)
		{
			ft_putstr_fd("Error command not found: ", 2);
			perror("");
		}
	}
	wait(NULL);	
}

void	executer(t_list *list, t_input *s)
{
	t_cmd	*cmd;
	char	**tab;

	while (list)
	{
		cmd = list->content;
		tab = ft_split(cmd->args, ' ');
		cmd->p_cmd = is_valid_cmd(tab[0], s->env);
		if (cmd->p_cmd)
			execute (cmd, tab, s);
		list = list->next;
	}

}
