/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/09 17:13:30 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	execute(t_cmd *cmd, char **args, t_input *s)
{
	char	**env;

	if (cmd->err_redir)
		err_msg_redir(cmd, s, 0);
	set_fds(cmd);
	close_fds(s);
	builtin(cmd, s);
	env = env_to_tab(s->env);
	cmd->cmd = is_valid_cmd(cmd, env, s);
	if (execve(cmd->cmd, args, env) == -1)
		err_execve(env, s);
}

void	process_recursion(t_cmd *list, t_input *s, int i, pid_t *f)
{
	t_cmd	*cmd;

	if (i >= s->nb_cmd)
		return ;
	cmd = cmd_index(list, i);
	f[i] = fork();
	set_last_pid(f[i]);
	if (f[i] == 0)
	{
		free(f);
		execute(cmd, cmd->cmd_args, s);
	}
	else
	{
		process_recursion(list, s, i + 1, f);
		close_fds(s);
	}
}

void	exe_builtin(t_cmd *cmd, t_input *s)
{
	t_coor	fds;

	if (!cmd->err_redir)
	{
		fds.i = dup(0);
		fds.j = dup(1);
		set_fds(cmd);
		builtin(cmd, s);
		close_fds(s);
		restore_fds(fds);
		close(fds.i);
		close(fds.j);
	}
	else
		err_msg_redir(cmd, s, 1);
}

void	executer(t_cmd *list, t_input *s)
{
	pid_t	*f;

	init_exec_signals();
	set_pipes(list, s);
	if (s->nb_cmd == 1 && list->args
		&& list->cmd_args && is_builtin(list->cmd_args[0]))
		exe_builtin(list, s);
	else
	{
		f = ft_calloc(s->nb_cmd, sizeof(pid_t));
		process_recursion(list, s, 0, f);
		wait_all(s, f);
		free(f);
	}
}
