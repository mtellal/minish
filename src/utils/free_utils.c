/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:00:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 17:09:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	free_pipes(t_input *s)
{
	int	i;

	i = 0;
	if (!s->pipes)
		return ;
	while (s->pipes[i])
	{
		free(s->pipes[i]);
		i++;
	}
}

void	free_all(t_input *s, int env)
{
	ft_lstclear_lexer(&s->tlist);
        ft_lstclear_token(&s->clist);
        clear_cmd_list(&s->cmd_list);
	free_pipes(s);
	if (env)
		free_env(s);
	if (s->hd)
		unlink(".heredoc");
}
