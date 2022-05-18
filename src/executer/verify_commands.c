/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:58:04 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/18 09:40:06 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**tab_path(char **env)
{
	char	**tab;

	if (!env || !*env)
		return (NULL);
	while (env && *env && ft_strncmp("PATH", *env, 4) != 0)
		env++;
	if (!*env)
		err("Error PATH problem", 0);
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

char	*is_valid_cmd(char *cmd, char **env)
{
	char	**p;
	char	*s;
	int		i;

	i = 0;
	p = tab_path(env);
	if (!p)
		return (NULL);
	while (p[i] && !valid_cmd(p[i], cmd))
		i++;
	if (p[i])
	{
		s = ft_strjoin_free(p[i], "/", 0, 0);
		s = ft_strjoin_free(s, cmd, 1, 0);
	}
	else
	{
		write(2, "Error: command not found: ", 26);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		s = ft_strdup(cmd);
	}
	free_tab(p);
	return (s);
}

/*
void	fill_commands(t_pip *s, int nbc)
{
	int	i;

	i = 0;
	while (i < nbc)
	{
		command(s->arg[i][0], s, i, s->data.env);
		i++;
	}
	if (s->err.cmd)
	{
		close_files(s);
		free_s(s, 1, 1, 1);
		err("", 0);
	}
}*/
