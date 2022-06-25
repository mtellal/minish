/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:17:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/24 17:32:49 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_exit(t_cmd *cmd, t_input *s)
{
	free_all(s);
	ft_putstr_fd("\nexit\n", 1);
	if (!cmd || ft_strlen_tab(cmd->cmd_args) == 1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
