/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:34:15 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 11:09:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**tab_path(char **env)
{
	char	**tab;
	int		i;

	i = 0;
	while (env && *env && ft_strncmp("PATH", *env, 4) != 0)
	{
		env++;
		i++;
	}
	if (!i)
	{
		ft_putstr_fd("error PATH", 2);
		return (NULL);
	}
	tab = ft_split(*env + 5, ':');
	return (tab);
}

int	valid_cmd(char *path, char *cmd)
{
	char	*c;
	char	*s;

	c = ft_strjoin_free(path, "/", 0, 0);
	s = ft_strjoin_free(c, cmd, 1, 0);
	if (access(s, F_OK && X_OK) == 0)
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

int	is_valid_cmd(char *cmd, t_input *s)
{
	int	i;
	char	**path;

	i = 0;
	path = tab_path(s->env);
	while (path && path[i])
	{
		if (valid_cmd(path[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	err_cmd(char	*cmd, t_input *s)
{
	if (!is_valid_cmd(cmd, s))
	{
		ft_putstr_fd("error: command not found ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n",2);
		return (1);
	}
	return (0);
}
