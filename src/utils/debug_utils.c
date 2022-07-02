/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:35:53 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/30 20:16:40 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    show_lexer(t_input *s)
{
        t_token *token;
        t_token	*r;
	int            i;
        char            *type;

        i = 0;
	r = s->tlist;
        type = NULL;
	while (s->tlist)
        {
		token = s->tlist;
                if (token->type == 0)
                        type = "ALPHANUMERIC";
                if (token->type == 1)
                        type = "REDIRECTION";
                if (token->type == 2)
                        type = "BRACKET";
                if (token->type == 3)
                        type = "PIPE";
                 if (token->type == 4)
                        type = "EXPAND";
                if (token->type == 5)
                        type = "SEPARATOR";
                if (token->type == 6)
                        type = "QUOTE";
                if (token->type == 7)
                        type = "ARITHMETIC";
                if (token->type == 8)
                        type = "OTHER";
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
	printf("\n");
}

