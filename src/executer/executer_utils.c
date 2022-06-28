/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:26:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/28 18:21:24 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	update_shlvl(t_input *s)
{
	t_env	*e;
	int	value;

	e = var_exists("SHLVL", s->env);
	if (e)
	{
		value = ft_atoi(get_var_value("SHLVL", s));
		set_var_value("SHLVL", ft_itoa(value + 1), s);
	}
}

int	is_minishell(char *s)
{
	int	len;
	char	*sub;

	sub = NULL;
	if (!s || !*s)
		return (0);
	len = ft_strlen(s);
	if (access(s, F_OK) != -1 && access(s, X_OK) != -1)
	{
		sub = ft_substr(s, len - 9, len);
		if (!ft_strcmp("minishell", sub))
		{
			free(sub);
			return (1);
		}
	}
	return (0);
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
	if (!ft_strcmp(scmd, "echo"))
		ft_echo(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "export"))
		ft_export(cmd->cmd_args, s);
	if (!ft_strcmp(scmd, "unset"))
		ft_unset(cmd->cmd_args, s);
	if (is_minishell(scmd))
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
