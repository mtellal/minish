/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:56:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 09:49:56 by mtellal          ###   ########.fr       */
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

void	close_fds_execute(t_input *s)
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

/*
 *	ne pas oublier les signaux + free la commande
 */

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

void	execute(t_cmd *cmd, char **args, t_input *s)
{
	set_fds(cmd->fdi, cmd->fdo);
	close_fds_execute(s);
	builtin(cmd, s);
	cmd->cmd = is_valid_cmd(cmd->cmd_args[0], s->f_env);
	if (execve(cmd->cmd, args, env_to_tab(s->env)) == -1)
	{
		ft_putstr_fd("Error command not found: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		//perror("");
	}
}

int	*pipe_env(t_cmd *cmd)
{
	int	*p;
	char	*scmd;

	p = NULL;
	scmd = cmd->cmd_args[0];
	if (!ft_strcmp(scmd, "export") || !ft_strcmp(scmd, "unset"))
	{
		p = ft_calloc(2, sizeof(int));
		if (pipe(p) == -1)
			return (NULL);
	}
	return (p);
}

/*
 *	ft_export => envoyer s->env dans une pipe
 */

void	executer(t_list *list, t_input *s)
{
	t_cmd	*cmd;
	pid_t	*f;
	int	i;

	i = 0;	
	set_pipes(list, s);
	//show_cmd_list(s->cmd_list);
	f = ft_calloc(s->nb_cmd, sizeof(pid_t));
	while (i < s->nb_cmd)
	{
		cmd = cmd_index(list, i);
		s->p_env = pipe_env(cmd);
		f[i] = fork();
		if (f[i] == -1)
			ft_putstr_fd("error fork\n", 2);
		if (f[i] == 0)
		{
			if (cmd->cmd_args)
				execute (cmd, cmd->cmd_args, s);
			else
			{
				ft_putstr_fd("bad p_cmd\n", 2);
				exit(0);
			}
		}
		signal(SIGINT, &redisplay);
		if (s->p_env)
		{
			if (!ft_strcmp(cmd->cmd_args[0], "export"))
				modify_env(s);
			if (!ft_strcmp(cmd->cmd_args[0], "unset"))
				modify_env(s);
		}
		if (cmd->fdi > 2)
			close(cmd->fdi);
		if (cmd->fdo > 2)
			close(cmd->fdo);
		i++;
	}
	wait_all(s, f);
}
