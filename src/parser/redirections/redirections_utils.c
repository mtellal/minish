/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:03:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/04 16:52:07 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	init_cmd_redir(t_utils *data, t_input *s, char *r)
{
	data->ptoken = list_index_token(s->clist, data->i_list - 1);
	data->ntoken = list_index_token(s->clist, data->i_list + 1);
	if (!data->ntoken)
		return (-1);
	data->cmd = cmd_index(s->cmd_list, data->i_cmd);
	data->tab = ft_split(data->ntoken->c, ' ');
	if (open_data(data, r) == -1)
	{
		perror("error");
		ft_lstclear_lexer(&s->tlist);
		ft_lstclear_token(&s->clist);
		return (-1);
	}
	return (0);
}

void	add_cmd(t_utils *data, t_input *s, char **rest_args, char *r)
{
	t_cmd	*_cmd;

	_cmd = NULL;
	if (data->ptoken && data->ptoken->type != SEPARATOR)
		*rest_args = ft_strjoin_free(data->ptoken->c, *rest_args, 0, 1);
	if (*r == '<')
	{
		_cmd = cmd(data->file, 1, *rest_args, data->i_cmd);
		ft_lstaddb_cmd(&s->cmd_list, _cmd);
	}
	if (*r == '>')
	{
		_cmd = cmd(0, data->file, *rest_args, data->i_cmd);
		ft_lstaddb_cmd(&s->cmd_list, _cmd);
	}
	progress_list(data, s, *rest_args);	
}

char	*join_tab(char **tab, int j)
{
	char	*t;

	t = NULL;
	while (tab[j])
	{
		if (!t)
			t = ft_strjoin_free(t, tab[j], 0, 0);
		else
			t = ft_strjoin_free(t, tab[j], 1, 0);
		t = ft_strjoin_free(t, " ", 1, 0);
		j++;
	}
	free_tab(tab);
	return (t);
}

void	modify_redirection(t_utils *data, char *rest_args, char *r)
{
	if (*r == '<')
		data->cmd->fdi = data->file;
	if (*r == '>')
		data->cmd->fdo = data->file;
	if (data->ntoken)
		data->ptoken->next = data->ntoken->next;
	else
		data->ptoken->next = data->ntoken;
	if (rest_args)
		data->cmd->args = ft_strjoin_free(data->cmd->args, rest_args, 0, 1);
}
