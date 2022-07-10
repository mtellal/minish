/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:26:30 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 16:18:24 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	update_shlvl(t_input *s)
{
	int		value;
	t_env	*e;

	e = var_exists("SHLVL", s->env);
	if (e)
	{
		value = ft_atoi(get_var_value("SHLVL", s));
		set_var_value("SHLVL", ft_itoa(value + 1), s);
	}
}

int	is_minishell(char *s)
{
	int		ls;
	char	*sub;

	sub = NULL;
	if (!s || !*s)
		return (0);
	ls = ft_strlen(s);
	if (s && ft_strlen(s) >= 11 && ((!ft_strcmp(s, "./minishell"))
			|| (!ft_strncmp(s, "./", 2) && !ft_strcmp(s + ls - 9, "minishell")))
		&& !access(s + 2, F_OK) && !access(s + 2, X_OK))
		return (1);
	else
		return (0);
}

void	builtin(t_cmd *cmd, t_input *s)
{
	char	*scmd;

	if (!cmd || !cmd->cmd_args)
		return ;
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
