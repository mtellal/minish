/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:35:53 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 19:18:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	show_lexer(t_input *s)
{
	int		i;
	t_token	*token;
	t_token	*r;
	char	*type;

	i = 0;
	r = s->tlist;
	type = NULL;
	while (s->tlist)
	{
		token = s->tlist;
		if (token->type == 0)
			type = "ALPHANUMERIC";
		if (token->type == 1)
			type = "SEPARATOR";
		ft_putchar_fd(*token->c, 1);
		ft_putstr_fd("		", 1);
		ft_putendl_fd(type, 1);
		s->tlist = s->tlist->next;
		i++;
	}
	s->tlist = r;
}

void	show_parser(t_input *s)
{
	t_token	*r;

	r = s->clist;
	ft_putstr_fd("show parser\n", 1);
	while (s->clist)
	{
		ft_putstr_fd("(", 1);
		ft_putstr_fd(s->clist->c, 1);
		ft_putstr_fd(")", 1);
		s->clist = s->clist->next;
	}
	s->clist = r;
	ft_putstr_fd("\n", 1);
}
