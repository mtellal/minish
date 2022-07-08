/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:14:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 13:40:34 by mtellal          ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	else
		cmd = ft_strdup(s);
	return (cmd);
}

void	err_msg_invalid_cmd(char *cmd, char **env, t_input *s)
{
	ft_putstr_fd("error: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_tab(env);
	free_all(s, 1);
	exit(127);
}
