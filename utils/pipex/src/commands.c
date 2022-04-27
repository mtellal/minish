/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:58:04 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 17:14:56 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**tab_path(char **env, t_pip *s)
{
	char	**tab;

	while (env && *env && ft_strncmp("PATH", *env, 4) != 0)
		env++;
	if (!*env)
		stop(s, "Err probleme de PATH", 0);
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

void	command(char *cmd, t_pip *st, int a, char **env)
{
	char	**p;
	char	*s;
	int		i;

	i = 0;
	p = tab_path(env, st);
	while (p[i] && !valid_cmd(p[i], cmd))
		i++;
	if (p[i])
	{
		s = ft_strjoin_free(p[i], "/", 0, 0);
		st->cmd[a] = ft_strjoin_free(s, cmd, 1, 0);
	}
	else
	{
		write(2, "Error: command not found: ", 26);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		st->cmd[a] = ft_strdup(cmd);
		st->err.cmd = 1;
	}
	free_tab(p);
}

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
		free_s(s, 1, 1, 1);
}
