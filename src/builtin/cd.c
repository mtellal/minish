/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:09:34 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 16:37:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	free_str(char *str)
{
	if (str)
		free(str);
}

char	*verif_paths(char *args, t_input *s)
{
	char	*var;

	if (!args)
	{
		var = get_var_value("HOME", s);
		if (!var || !*var)
		{
			free_str(var);
			ft_putstr_fd("error: cd: HOME undefined\n", 2);
			return (NULL);
		}
	}
	else if (args[0] == '-' && !args[1])
	{
		var = get_var_value("OLDPWD", s);
		if (!var || !*var)
		{
			free_str(var);
			ft_putstr_fd("error: cd: OLDPWD undefined\n", 2);
			return (NULL);
		}
	}
	else
		return (ft_strdup(args));
	return (var);
}

int	set_paths(t_input *s, char *var)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_var_value("OLDPWD", s);
	pwd = get_var_value("PWD", s);
	if (!pwd)
	{
		free(var);
		free(oldpwd);
		ft_putstr_fd("error: cd: PWD undefined\n", 2);
		return (-1);
	}
	else
		set_var_value("OLDPWD", pwd, s);
	if (var && oldpwd && !ft_strcmp(var, oldpwd))
		set_var_value("PWD", oldpwd, s);
	if (oldpwd)
		free(oldpwd);
	free(pwd);
	free(var);
	ft_pwd(1, s);
	return (0);
}	

void	ft_cd(char **args, t_input *s)
{
	char	*var;

	if (ft_strlen_tab(args) > 2)
	{
		ft_putstr_fd("error: cd: too many arguments\n", 2);
		return (return_status(EXIT_FAILURE, s));
	}
	var = verif_paths(args[1], s);
	if (var)
	{
		if (chdir(var) == -1)
		{
			perror("cd");
			free(var);
			return (return_status(2, s));
		}
		if (set_paths(s, var) == -1)
			return (return_status(2, s));
	}
	return (return_status(0, s));
}
