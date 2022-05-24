/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:26:18 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 15:35:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int     last_quote_in_word(char *s, char quote)
{
        int     i;

        i = 0;
        while (s[i])
        {
                if (s[i] == ' ')
                        return (1);
                if (s[i] == quote)
                        return (0);
                i++;
        }
        return (1);
}

int     first_quote_in_word(char *s, int index, char quote)
{
        int     i;

        i = index;
        while (i > 0)
        {
                if (s[i] == ' ')
                        return (1);
                if (s[i] == quote)
                        return (0);
                i--;
        }
        return (1);
}
