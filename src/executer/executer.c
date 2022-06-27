/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 14:49:20 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	execute(t_cmd *cmd, char **args, t_input *s)
{
	char	**env;

	if (cmd->err_redir)
		err_cmd(cmd, s, 0);
	set_fds(cmd);
	close_fds(s);
	builtin(cmd, s);
	env = env_to_tab(s->env);
	cmd->cmd = is_valid_cmd(cmd->cmd_args[0], env);
	if (execve(cmd->cmd, args, env) == -1)
		err_cmd(cmd, s, 1);
}

void	process_recursion(t_cmd *list, t_input *s, int i, pid_t *f)
{
	t_cmd	*cmd;

	if (i >= s->nb_cmd)
		return ;
	cmd = cmd_index(list, i);
        s->p_env = pipe_env(cmd, s->nb_cmd);
	f[i] = fork();
	if (f[i] == -1)
		ft_putstr_fd("err forking\n", 2);
	if (f[i] == 0)
		execute(cmd, cmd->cmd_args, s);
	else
	{
		process_recursion(list, s, i + 1, f);
		close_fds(s);
		err_msg_redirection(cmd->err_redir);
		if (s->nb_cmd == 1 && s->p_env)
			need_update_env(cmd, s);
	}
}

void	exe_builtin(t_cmd *cmd, t_input *s)
{
	builtin(cmd, s);
	close_fds(s);
	err_msg_redirection(cmd->err_redir);
}

void	executer(t_cmd *list, t_input *s)
{
	pid_t	*f;

	signal(SIGINT, &redisplay);
	set_pipes(list, s);
	
	//show_cmd_list(s->cmd_list);
	//ft_putstr_fd("\n", 1);
	
	if (s->nb_cmd == 1 && is_builtin(list->cmd_args[0]))
		exe_builtin(list, s);
	else
	{
		f = ft_calloc(s->nb_cmd, sizeof(pid_t));
		process_recursion(list, s, 0, f);
		wait_all(s, f);
	}
	close_pipes(s->pipes);
}
