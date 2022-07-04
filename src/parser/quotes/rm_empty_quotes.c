/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:26:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 15:39:02 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     rm_d_quotes(char c, char c2, int i)
{
        if ((c != ' ' && c != '\0'))
                return (1);
        if (i > 0 && (c2 != ' '))
                return (1);
        return (0);
}

int     skip_quotes(char *quote, int *j, char *s)
{
        int     i;

        i = *j;
        if (s[i] && ft_belong("'\"", s[i])
                && s[i] == *quote && s[i + 1] == *quote &&
		s[i + 2] && i > 0 && rm_d_quotes(s[i + 2], s[i - 1], i))
                {
                        *j += 2;
                        *quote = 0;
                        return (1);
                }
        return (0);
}


char    *remove_empty_quotes(char *s)
{
        char    quote;
        int             i;
        char    *final;

        i = 0;
        final = NULL;
        quote = 0;
        while (s && s[i])
        {
                if (!quote && ft_belong("'\"", s[i]))
                        quote = s[i];
                else if (quote && quote == s[i])
                        quote = 0;
                if (!skip_quotes(&quote, &i, s))
                {
                        final = add_char(final, s[i]);
                        i++;
                }
        }
	if (s)
		free(s);
        return (final);
}
