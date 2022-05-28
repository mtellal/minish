/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:17:10 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/28 12:44:09 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	**tab_path(char **env)
{
	char	**tab;

	if (!env || !*env)
		return (NULL);
	while (env && *env && ft_strncmp("PATH", *env, 4) != 0)
		env++;
	if (!*env)
		ft_putstr_fd("err PATH invalid\n", 2);	
	tab = ft_split(*env + 5, ':');
	return (tab);
}

int	valid_cmd(char *path, char *cmd)
{
	char	*c;
	char	*s;

	c = ft_strjoin_free(path, "/", 0, 0);
	s = ft_strjoin_free(c, cmd, 1, 0);
	if (access(s, F_OK) == 0)
	{
		if (access(s, X_OK) == -1)
		{
			perror("error:");
			exit(0);
		}
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

char	**add_tab_first(char *s, char **tab)
{
	char	**f;
	int	i;

	i = 0;
	if (!s)
		return (tab);
	f = ft_calloc(ft_strlen_tab(tab) + 2, sizeof(char*));
	f[0] = ft_strdup(s);
	while (tab && tab[i])
	{
		f[i + 1] = ft_strdup(tab[i]);
		i++;
	}
	f[i + 1] = NULL;
	//if (tab)
	//	free_tab(tab);
	//free(s);
	return (f);
}

char	*wrap_bash(char *s)
{
	char	*cmd;

	cmd = NULL;
	if (access(s, X_OK) == -1)
	{
		perror("error:");
		exit(0);
	}
	cmd = ft_strdup(s);
	return (cmd);
}

char	*is_valid_cmd(char *cmd, char **env)
{
	char	**p;
	char	*s;
	int		i;

	i = 0;
	s = NULL;
	if (access(cmd, F_OK) == 0)
		return (wrap_bash(cmd));
	else
	{
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
			exit(0);
		}
		free_tab(p);
	}
	return (s);
}


