/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/22 21:35:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_fds(int fdi, int fdo)
{
	if (fdi > 2 && dup2(fdi, 0) == -1)
	{
		ft_putstr_fd("err dup2\n", 2);
		exit(0);
	}
	if (fdo > 2 && dup2(fdo, 1) == -1)
	{
		ft_putstr_fd("err dup2\n", 2);
		exit(0);
	}
}

void	close_fds(t_input *s)
{
	t_cmd	*cmd;
	t_list	*list;

	list = s->cmd_list;
	while (list)
	{
		cmd = list->content;
		if (cmd && cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd && cmd->fdo > 2)
			close(cmd->fdo);
		list = list->next;
	}
}

void	execute(t_cmd *cmd, char **args, t_input *s)
{
		set_fds(cmd->fdi, cmd->fdo);
		close_fds(s);
		if (execve(cmd->cmd, args, s->env) == -1)
		{
			ft_putstr_fd("Error command not found: ", 2);
			perror("");
		}
}

void	executer(t_list *list, t_input *s)
{
	t_cmd	*cmd;
	pid_t	f;
	
	set_pipes(list, s);
	while (list)
	{
		cmd = list->content;
		f = fork();
		if (f == -1)
			ft_putstr_fd("error fork\n", 2);
		if (f == 0)
		{
			cmd->cmd_args = ft_split(cmd->args, ' ');
			cmd->cmd = is_valid_cmd(cmd->cmd_args[0], s->env);
			if (cmd->cmd)
				execute (cmd, cmd->cmd_args, s);
			else
				ft_putstr_fd("bad p_cmd\n", 2);
		}
		if (cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd->fdo > 2)
			close(cmd->fdo);
		if (waitpid(f, NULL, 0) == -1)
			ft_putstr_fd("err waitpid", 2);
		list = list->next;
	}
}
