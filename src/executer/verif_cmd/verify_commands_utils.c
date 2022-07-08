/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:14:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/08 17:00:52 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*wrap_bash(char *s, char **env, t_input *ss)
{
	char	*cmd;

	cmd = NULL;
	if (!ft_strncmp(s, "./", 2) && access(s, X_OK) == -1)
	{
		perror("error");
		free_tab(env);
		free_all(ss, 1);
		exit(126);
	}
	else
		cmd = ft_strdup(s);
	return (cmd);
}

void	err_msg_invalid_cmd(char *cmd, char **env, t_input *s)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(env);
	free_all(s, 1);
	exit(127);
}

void	err_msg_redir(t_cmd *c, t_input *s, int builtin)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(c->err_redir, 2);
	if (s->nb_cmd > 1)
		free_all(s, 1);
	if (builtin)
		set_last_status(EXIT_FAILURE);
	else
		exit(EXIT_FAILURE);
}

void	err_execve(char **env, t_input *s)
{
	free_tab(env);
	perror("error: ");
	free_all(s, 1);
	exit(EXIT_FAILURE);
}
