/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:26:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 11:34:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	need_update_env(t_cmd *cmd, t_input *s)
{
	char	*ccmd;

	ccmd = cmd->cmd_args[0];
	if (s->p_env && s->nb_cmd == 1)
	{
		if (!ft_strcmp(ccmd, "export") || !ft_strcmp(ccmd, "unset"))
			update_env(s);
	}
}

void	update_shlvl(t_input *s)
{
	t_env	*e;
	int	value;

	e = var_exists("SHLVL", s->env);
	if (e)
	{
		ft_putstr_fd("SHLVL\n", 1);
		value = ft_atoi(get_var_value("SHLVL", s));
		set_var_value("SHLVL", ft_itoa(value + 1), s);
	}
}

int	*pipe_env(t_cmd *cmd, int nb_cmd)
{
	int		*p;
	char	*scmd;

	p = NULL;
	if (!cmd->args || nb_cmd != 1)
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
	if (!ft_strcmp(scmd, "exit"))
		ft_exit(cmd, s);
	if (!ft_strcmp(scmd, "env"))
		ft_env(s->env, s);
	if (!ft_strcmp(scmd, "pwd"))
		ft_pwd(0, s);
	if (!ft_strcmp(scmd, "exit"))
		exit(EXIT_SUCCESS);
	if (!ft_strcmp(scmd, "echo"))
		ft_echo(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "export"))
		ft_export(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "unset"))
		ft_unset(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "./minishell"))
		update_shlvl(s);
	if (!ft_strcmp(scmd, "cd"))
		ft_cd(cmd->cmd_args, s);
}

int	is_builtin(char *args)
{
	int			i;
	static char	*tab[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(tab[i], args))
			return (1);
		i++;
	}
	return (0);
}
