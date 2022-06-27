/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:09:34 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 14:31:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	return_status(int status, t_input *s)
{
	if (s->nb_cmd > 1)
		exit(status);
	else
		s->lstatus = status;
}

char	*verif_paths(char *args, t_input *s)
{
	char	*var;

	if (!args)
	{
		var = get_var_value("HOME", s);
		if (!var || !*var)
		{
			ft_putstr_fd("error: cd: HOME undefined\n", 2);
			return (NULL);
		}
	}
	if (args[0] == '-' && !args[1])
	{
		var = get_var_value("OLDPWD", s);
		if (!var || !*var)
		{
			ft_putstr_fd("error: cd: OLDPWD undefined\n", 2);
			return (NULL);
		}
	}
	else
		return (args);
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
		ft_putstr_fd("error: cd: PWD undefined\n", 2);
		return (-1);
	}
	else
		set_var_value("OLDPWD", pwd, s);
	if (!ft_strcmp(var, oldpwd))
		set_var_value("PWD", oldpwd, s);
	ft_pwd(1, s);
	return (0);
}	

void	ft_cd(char **args, t_input *s)
{
	char	*var;

	ft_putstr_fd("cd called\n", 2);
	if (args[2])
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
                        return (return_status(EXIT_FAILURE, s));
                }
		if (set_paths(s, var) == -1)
			return (return_status(EXIT_FAILURE, s));
	}
	return (return_status(0, s));
}
