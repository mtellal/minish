/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:26:38 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/23 16:38:56 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	launch_parser(t_input *s)
{
	lexer(s);
	parser(s);
	clear_space(s->clist);
}

void	launch_separators(t_input *s)
{
	 if (index_separator(s->clist) == -1)
                       ft_lstaddb_cmd(&s->cmd_list, cmd(0, 1, s->clist->c, 0));
        else
                cmd_redirections(s->clist, s);
	cmd_pipes(s->clist, s);
        s->nb_cmd = ft_lstsize_cmd(s->cmd_list);
}

void	launch_executer(t_input *s)
{
	fill_args(s->cmd_list, s);
        executer(s->cmd_list, s);
}
