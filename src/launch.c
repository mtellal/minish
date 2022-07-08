/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:26:38 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 17:49:49 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	launch_parser(t_input *s)
{
	lexer(s);
	parser(s);
	clear_space(s->clist, s);
	quote_cleaner(s);
	clear_space(s->clist, s);
}

void	launch_separators(t_input *s)
{
	if (index_separator(s->clist) == -1)
		ft_lstaddb_cmd(&s->cmd, cmd(0, 1, s->clist->c, 0));
	else
		cmd_redirections(s->clist, s);
	cmd_pipes(s->clist, s);
	s->nb_cmd = ft_lstsize_cmd(s->cmd);
	fill_args(s->cmd, s);
}

void	launch_executer(t_input *s)
{
	if (!get_quit_hd())
		executer(s->cmd, s);
	else
		set_quit_hd(0);
}
