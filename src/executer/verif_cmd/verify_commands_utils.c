/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:14:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/09 21:50:29 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*wrap_bash(char *s, char **env, t_input *ss)
{
	int		err_status;
	char	*cmd;

	cmd = NULL;
	err_status = 0;
	if (access(s + 2, F_OK) == -1)
		err_status = 127;
	if (!err_status && access(s + 2, X_OK) == -1)
		err_status = 126;
	if (err_status)
	{
		perror("error");
		free_tab(env);
		free_all(ss, 1);
		exit(err_status);
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
	exit(127);
}
