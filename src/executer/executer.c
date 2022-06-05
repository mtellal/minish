/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/04 19:40:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_fds(t_cmd *cmd)
{
	if (cmd->fdi > 2 && dup2(cmd->fdi, 0) == -1)
	{
		ft_putstr_fd("\nerr dup2 ", 2);
		ft_putstr_fd(cmd->args, 2);
		ft_putstr_fd(" ", 2);
		ft_putnbr_fd(cmd->fdi, 2);
		ft_putstr_fd("\n", 2);
		perror("");
		exit(0);
	}
	if (cmd->fdo > 2 && dup2(cmd->fdo, 1) == -1)
	{
		ft_putstr_fd("\nerr dup2 ", 2);
                ft_putstr_fd(cmd->args, 2);
                ft_putstr_fd(" ", 2);
                ft_putnbr_fd(cmd->fdo, 2);
                ft_putstr_fd("\n", 2);
		perror("");
		exit(0);
	}
}

void	close_fds(t_input *s)
{
	t_cmd	*cmd;

	cmd = s->cmd_list;
	while (cmd)
	{
		if (cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd->fdo > 2)
			close(cmd->fdo);
		cmd = cmd->next;
	}
}

void	execute(t_cmd *cmd, char **args, t_input *s)
{
	set_fds(cmd);
	close_fds(s);
	builtin(cmd, s);
	cmd->cmd = is_valid_cmd(cmd->cmd_args[0], s->f_env);
	if (execve(cmd->cmd, args, env_to_tab(s->env)) == -1)
	{
		ft_putstr_fd("Error command not found: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
	}
}

void	process_recursion(t_cmd *list, t_input *s, int i)
{
	t_cmd	*cmd;
	pid_t	f;

	if (i >= s->nb_cmd)
		return ;
	cmd = cmd_index(list, i);
        s->p_env = pipe_env(cmd);
	f = fork();
	if (f == -1)
		ft_putstr_fd("err forking\n", 2);
	if (f == 0)
		execute(cmd, cmd->cmd_args, s);
	else
	{
		process_recursion(list, s, i + 1);
		close_fds(s);
		wait(NULL);
		signal(SIGINT, &redisplay);
                need_update_env(cmd, s);
	}
}

void	executer(t_cmd *list, t_input *s)
{
	set_pipes(list, s);
	show_cmd_list(s->cmd_list);
	process_recursion(list, s, 0);
	//wait_all(s, f);
}
