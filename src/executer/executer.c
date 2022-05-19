/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/19 11:44:08 by mtellal          ###   ########.fr       */
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
		if (execve(cmd->p_cmd, args, s->env) == -1)
		{
			ft_putstr_fd("Error command not found: ", 2);
			perror("");
		}
}

void	executer(t_list *list, t_input *s)
{
	t_cmd	*cmd;
	char	**tab;
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
			tab = ft_split(cmd->args, ' ');
			cmd->p_cmd = is_valid_cmd(tab[0], s->env);
			if (cmd->p_cmd)
				execute (cmd, tab, s);
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
