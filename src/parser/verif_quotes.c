/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:22:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/20 18:15:36 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	nb_char(char *s, char c)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

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

char	*clear_same_quotes(char *tab, char c)
{
	int	i;
	int	j;
	char	*s;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (tab[i])
	{
		if (tab[i] != c)
		{
			len++;
			i++;
		}
		else
			i++;
	}
	i = 0;
	s = ft_calloc(len + 1, sizeof(char));
	while (tab[i])
	{
		if (s[j] != c)
		{
			j++;
			i++;
		}
		else
			i++;
	}
	s[j] = '\0';
	return (s);
}

char	*clear_quotes(char *s)
{
	int	f_index;
	int	l_index;
	char	*ss;
	char	*tab;
	int	i;
	char	quote;

	if (!s || !*s)
		return (NULL);
	i = 0;
	quote = index_quote(s, 0);
	if (quote == -1)
		return (s);
	while (s[i])
	{
		f_index = index_quote(s, quote);
		if (f_index == -1)
			break;
		l_index = index_quote(s + f_index + 1, quote);
		if (l_index == -1)
			break;
		tab = ft_substr(s, f_index, l_index);
		tab = clear_same_quotes(tab, s[f_index]);
		f_index = l_index + 1;
		if (!ss)
			ss = ft_strdup(tab);
		else
			ft_strjoin_free(ss, tab, 1, 1);
		i += f_index;
	}
	return (ss);
}

int     msg_err_quote(void)
{
        ft_putstr_fd("error: unclosed quote ", 2);
        ft_putstr_fd("\n", 2);
        return (-1);
}

int	err_quotes(t_list *list)
{
	t_cmd	*cmd;

	while (list)
	{
		cmd = list->content;
		if (wrong_number_quote(cmd->args))
			return (msg_err_quote());
		else
			clear_quotes(cmd->args);
		ft_putstr_fd(cmd->args, 2);
		list = list->next;
	}
	return (0);
}
