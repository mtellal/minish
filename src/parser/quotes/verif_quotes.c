/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/26 20:15:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	index_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (c == 0)
		{
			if (s[i] == '\'' || s[i] == '\"')
				return (i);
		}
		else if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	wrong_number_quote(char *s)
{
	int	f_index;
	int	l_index;
	char	quote;
	int	q_index;

	q_index = index_quote(s, 0);
	if (q_index == -1)
		return (0);
	quote = s[q_index];
	while(*s)
	{
		f_index = index_quote(s, quote);
		s += f_index + 1;
		l_index = index_quote(s, quote);
		if (l_index == -1 && f_index != -1)
			return (-1);
		s += l_index + 1;
		q_index = index_quote(s, 0);
		quote = s[q_index];
		if (q_index == -1)
			return (0);
	}
	return (0);
}

int	len_rm_empty_quotes(char *s)
{
        int     i;
        char    quote;
	int	len;

        i = 0;
        quote = 0;
        while (s[i])
        {
                if (s[i] == '\'' || s[i] == '\"')
                {
                        if (!quote)
                                quote = s[i];
                        if (s[i] == quote && s[i + 1] && s[i + 1] == quote)
                        {
                                quote = 0;
                                i += 2;
                        }
                        else
                        {
                                len++;
                                i++;
                        }
                }
                else
                {
                        i++;
                        len++;
                }
        }
	return (len);
}

char	*remove_empty_quotes(char *s)
{
	char	*ns;
	int	f_quote;
	int	l_quote;
	char	quote;
	int	i;

	ns = NULL;
	i = 0;
	while (1)
	{
		f_quote = index_quote(s + i, 0);
		if (f_quote == -1)
		{
			if (s[i])
				ns = ft_strjoin_free(ns, ft_substr(s + i, 0, ft_strlen(s + i)), 1, 1);
			return (ns);
		}
		quote = s[i + f_quote];
		if (f_quote > 0)
			ns = ft_strjoin_free(ns, ft_substr(s + i, 0, f_quote), 1, 1);
		i += f_quote;
		l_quote = index_quote(s + i + 1, quote);
		if (l_quote == -1)
		{
			free(ns);
			return (NULL);
		}
		if (l_quote == 0)
			i += 2;
		
		else
		{
			ns = ft_strjoin_free(ns, ft_substr(s + i, 0, l_quote + 2), 1, 1);
			i += l_quote + 2;
		}
	}
	return (ns);
}

int     msg_err_quote(void)
{
        ft_putstr_fd("error: unclosed quote ", 2);
        ft_putstr_fd("\n", 2);
        return (-1);
}

int	err_quotes(char *buffer, char **input)
{
	char	*s;

	s = remove_empty_quotes(buffer);
	if (!s || (index_quote(buffer, 0) != -1  && wrong_number_quote(s)))
			return (msg_err_quote());
	free(*input);
	*input = s;
	return (0);
}
