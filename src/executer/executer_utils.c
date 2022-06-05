/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:26:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/04 13:59:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	need_update_env(t_cmd *cmd, t_input *s)
{
	if (s->p_env)
	{
		if (!ft_strcmp(cmd->cmd_args[0], "export"))
			update_env(s);
		if (!ft_strcmp(cmd->cmd_args[0], "unset"))
			update_env(s);
	}
}

void	close_fd_cmd(t_cmd *cmd)
{
	if (cmd->fdi > 2)
		close(cmd->fdi);
	if (cmd->fdo > 2)
		close(cmd->fdo);
}

int	*pipe_env(t_cmd *cmd)
{
	int		*p;
	char	*scmd;

	p = NULL;
	if (!cmd->args)
		return (NULL);
	scmd = cmd->cmd_args[0];
	if (!ft_strcmp(scmd, "export") || !ft_strcmp(scmd, "unset"))
	{
		p = ft_calloc(2, sizeof(int));
		if (pipe(p) == -1)
			return (NULL);
	}
	return (p);
}

void	builtin(t_cmd *cmd, t_input *s)
{
	char	*scmd;

	scmd = cmd->cmd_args[0];
	if (!ft_strcmp(scmd, "env"))
		ft_env(s->env);
	if (!ft_strcmp(scmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(scmd, "exit"))
		exit(EXIT_SUCCESS);
	if (!ft_strcmp(scmd, "echo"))
		ft_echo(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "export"))
		ft_export(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "unset"))
		ft_unset(cmd->cmd_args, s);
}
