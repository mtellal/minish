/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:18:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 10:18:37 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_cmd	*cmd(int fdi, int fdo, char *args, int id)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdi = fdi;
	cmd->fdo = fdo;
	cmd->args = ft_strdup(args);
	cmd->id = id;
	cmd->cmd = NULL;
	cmd->cmd_args = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	index_separator(t_token *list)
{
	int		i;
	t_token	*r;

	i = 0;
	r = list;
	while (list)
	{
		if (list->type == SEPARATOR && !only_space(list->c))
			return (i);
		list = list->next;
		i++;
	}
	list = r;
	return (-1);
}

int	nb_token_type(t_token *list, enum e_type type)
{
	int		i;
	t_token	*r;

	i = 0;
	r = list;
	while (list)
	{
		if (list->type == type)
			i++;
		list = list->next;
	}
	list = r;
	return (i);
}
