/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:00:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/08 22:16:31 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	free_all(t_input *s)
{
	ft_lstclear_lexer(&s->tlist);
        ft_lstclear_token(&s->clist);
        clear_cmd_list(&s->cmd_list);
	if (s->hd)
		unlink(".heredoc");
}
