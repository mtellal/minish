/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:27:22 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/02 18:09:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char    *clear_word(char *s)
{
        char    *final;
        char    quote;
        t_coor  x;

        x.i = 0;
        quote = 0;
        if (!s || !*s)
                return (NULL);
        final = ft_strdup("'");
	while (s && s[x.i])
        {
                if (!quote && ft_belong("'\"", s[x.i]))
                        quote = s[x.i];
                else if (quote && ft_belong("'\"", s[x.i]) && s[x.i] == quote)
                        quote = 0;
                else
                        final = add_char(final, s[x.i]);
                x.i++;
        }
        final = ft_strjoin_free(final, "'", 1, 0);
	return (final);
}

char    *merge_quotes(char **tab)
{
	int		n;
	int		i;
        char    **final;
        char    *s;

	s = NULL;
        i = 0;
	n = 0;
	final = clear_tab(tab);
        while (final && final[i])
        {
                n = nb_quotes(final[i]);
                if (n)
                        final[i] = clear_word(final[i]);
                if (ft_strlen(final[i]) > 2 && final[i][0] == '\'')
			final[i] = ft_substr_free(final[i], 1, ft_strlen(final[i]) - 2, 1);
		if (type_token(final[i][0]) == ALPHANUM)
			s = ft_strjoin_free(s, " ", 1, 0);
		s = ft_strjoin_free(s, final[i], 1, 0);
                i++;
        }
        return (s);
}

char    *clear_str(char *s)
{
        char    *final;
        char    **tab;

        tab = NULL;
        final = remove_empty_quotes(s);
        tab = ft_split(final, ' ');
        final = merge_quotes(tab);
        return (final);
}

void    quote_cleaner(t_input *s)
{
        t_token *list;

        list = s->clist;
        while (list)
        {
                list->c = clear_str(list->c);
                list = list->next;
        }
}

