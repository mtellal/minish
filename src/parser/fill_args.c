/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:57:26 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/02 18:08:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	fill_args(t_cmd *cmd, t_input *s)
{
	int	i;
	char	**args;

	i = 0;
	while (i < s->nb_cmd)
	{
		cmd = cmd_index(cmd, i);
		args = ft_split(cmd->args, ' ');
		cmd->cmd_args = clear_tab(args);
		i++;
	}
}
