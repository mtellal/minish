/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_separator_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:04:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 10:12:19 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	msg_err_separator(char *s, int err_sep)
{
	ft_putstr_fd("error: syntax token '", 2);
	ft_putchar_fd(s[err_sep], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	same_char(char *s, char c, int l)
{
	int	i;

	i = 0;
	while (s[i] == c && i < l)
		i++;
	if (i == l)
		return (-1);
	return (i);
}

int	valid_separator(char *s, int *err_sep)
{
	int		l;
	char	*tab;

	tab = "<>";
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

int	err_redi(t_token *list, t_token *nlist)
{
	int	err_sep;

	err_sep = 0;
	if (valid_separator(list->c, &err_sep) != -1)
		return (msg_err_separator(list->c, err_sep));
	if (!nlist || nlist->type == SEPARATOR)
		return (msg_err_separator(list->c, 0));
	return (0);
}
