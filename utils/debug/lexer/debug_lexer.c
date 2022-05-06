/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:11:04 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:52 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void    show_token_list(t_input *s)
{
        t_list  *list;
        t_token *token;
        int            i;
        char            *type;

        list = s->tlist;
        token = list->content;
        i = 0;
        type = NULL;
        while (i < s->llist)
        {
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
                printf("%c      %s\n",*(char*)(token->c), type );
                list = list->next;
                if (list)
                        token = list->content;
                i++;
        }
}
