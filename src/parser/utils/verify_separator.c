/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:54:08 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 11:19:13 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     ft_belong(char *s, char c)
{
        int     i;

        i = 0;
        while (s[i])
        {
                if (s[i] == c)
                        return (1);
                i++;
        }
        return (0);
}

//      verifie si l char dans s sont bien c, utile pour << et >>

int     same_char(char *s, char c, int l)
{
        int     i;

        i = 0;
        while (s[i] == c && i < l)
                i++;
        if (i == l)
                return (-1);
        return (i);
}

//      verifie si les separateurs (| > < >> << & ;) sont bien respectes

int     valid_separator(char    *s, int *err_sep)
{
        int     l;
        char    *tab;

        tab = "|<>&;";
        l = ft_strlen(s);
        *err_sep = 0;
        if (l == 2)
        {
                if (s[0] == '<')
                        *err_sep = same_char(s, '<', 2);
                else if (s[0] == '>')
                        *err_sep = same_char(s, '>', 2);
        }
        else if (ft_belong(tab, s[0]))
        {
                if (s[1] == '\0')
                        *err_sep = -1;
                else
                        *err_sep = 1;
        }
        return (*err_sep);
}

int     msg_err_separator(char *s, int err_sep)
{
                ft_putstr_fd("error: syntax token '", 2);
                ft_putchar_fd(s[err_sep], 2);
                ft_putstr_fd("'\n", 2);
                return (1);
}


int     err_separator(t_list *list, t_input *s)
{
        t_token *token;
        int     err_sep;

        while (list)
        {
                token = list->content;
                if (token->type == SEPARATOR)
                {
			if (s->llist == 1)
				return (msg_err_separator(token->c, 0));
			//	si il y a bien '<' '<<' '>>' '>' '|' '&' ';'
                        if (valid_separator(token->c, &err_sep) != -1)
                                return (msg_err_separator(token->c, err_sep));
			//	si il y a bien une commande apres le separateur (sauf pour ';')
               		if (*token->c != ';' && !list->next)
				return (msg_err_separator(token->c, 0));
			//	s_clist = 'ls ' '|' ' ' ';' -> apres clear_space 'ls ' '|' ';' (2 sep colles)
	       		if (list->next)
			{
				token = list->next->content;
				if (token->type == SEPARATOR && (*token->c == ';' || *token->c == '&'))
					return (msg_err_separator(token->c, 0));
			}
		}
                list = list->next;
        }
        return (0);
}
