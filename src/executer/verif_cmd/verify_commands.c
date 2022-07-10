/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:17:10 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 16:23:50 by mtellal          ###   ########.fr       */
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
		return (NULL);
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
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

char	**add_tab_first(char *s, char **tab)
{
	char	**f;
	int		i;

	i = 0;
	if (!s)
		return (tab);
	f = ft_calloc(ft_strlen_tab(tab) + 2, sizeof(char *));
	f[0] = ft_strdup(s);
	while (tab && tab[i])
	{
		f[i + 1] = ft_strdup(tab[i]);
		i++;
	}
	f[i + 1] = NULL;
	return (f);
}

char	*wrap_binary(char *cmd, char **env)
{
	int		i;
	char	**p;
	char	*s;

	s = NULL;
	i = 0;
	p = tab_path(env);
	if (cmd[0] != '/' && p)
	{
		while (p[i] && !valid_cmd(p[i], cmd))
			i++;
		if (p[i])
			s = ft_strjoin_free(ft_strjoin(p[i], "/"), cmd, 1, 0);
	}
	if (!p || !p[i] || (cmd && cmd[0] == '/'))
		s = ft_strdup(cmd);
	free_tab(p);
	return (s);
}

char	*is_valid_cmd(t_cmd *scmd, char **env, t_input *s)
{
	char	*cmd;

	if (!scmd->cmd_args)
		err_msg_invalid_cmd(NULL, env, s);
	cmd = scmd->cmd_args[0];
	if (ft_strlen(cmd) == 1 && !ft_strcmp(cmd, "."))
	{
		ft_putstr_fd("error: file name needed for argument\n", 2);
		free_tab(env);
		free_all(s, 1);
		exit (2);
	}
	if (ft_strlen(cmd) == 2 && !ft_strcmp(cmd, ".."))
		err_msg_invalid_cmd(cmd, env, s);
	if (ft_strlen(cmd) >= 2 && !ft_strncmp(cmd, "./", 2))
		return (wrap_bash(cmd, env, s));
	else
		return (wrap_binary(cmd, env));
}
