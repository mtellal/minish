/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 15:19:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     f_word(char *s, int i)
{
        while (s[i] && i > 0)
        {
                if (i - 1 > 0 && s[i - 1] == ' ')
                {
                        if (s[i] != '\'')
                                return (i);
                        else
                                return (-1);
                }
                i--;
        }
        if (i == 0 && s[i] != '\'')
                return (0);
        return (-1);
}

int     l_word(char *s, int i)
{
        while (s[i])
        {
                if (s[i + 1] && s[i + 1] == ' ')
                {
                        if (s[i] != '\'')
                                return (i);
                        else
                                return (-1);
                }
                i++;
        }
        if (!s[i] && s[i - 1] && s[i - 1] != '\'' && s[i - 1] != ' ')
                return (i - 1);
        return (-1);
}

int     next_space(char *s)
{
        int     i;

        i = 0;
        while (s[i])
        {
                if (s[i] == ' ')
                        return (i);
                i++;
        }
        if (s[i - 1])
                return (i - 1);
        return (i);
}

int     index_quote_end(char *s)
{
        int     i;

        i = ft_strlen(s) - 1;
        while (i > 0)
        {
                if (s[i] == '\'')
                        return (i);
                i--;
        }
        return (-1);
}

char    *expand_quotes(char *s)
{
        char    *ns;
        int     i_quote;
        int     i_word;

        ns = NULL;
        while (1)
        {
                i_quote = index_quote(s, '\'');
                if (i_quote == -1)
                {
                        if (*s)
                                ns = ft_strjoin_free(ns, ft_substr(s, 0, ft_strlen(s) + 1), 1, 1);
                        return (ns);
                }
                i_word = f_word(s, i_quote);
                if (i_word != -1)
                {
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, i_word), 1, 1);
                        ns = ft_strjoin_free(ns, "'", 1, 0);
                        s += i_word;
                        i_quote = index_quote(s, '\'');
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, i_quote), 1, 1);
                }
                else
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, i_quote + 1), 1, 1);
                s += i_quote + 1;
                i_quote = index_quote_end(s);
                if (i_quote != -1)
                {
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, i_quote), 1, 1);
                        s += i_quote + 1;
                }
                i_word = l_word(s, 0);
                if (i_word != -1)
                {
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, i_word + 1), 1, 1);
                        s += i_word + 1;
                }
                else
                {
                        ns = ft_strjoin_free(ns, ft_substr(s, 0, next_space(s) + 1), 1, 1);
                        s += next_space(s) + 1;
                }
        }
        return (NULL);
}


