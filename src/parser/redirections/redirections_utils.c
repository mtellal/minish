/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:03:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/09 11:59:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	err_msg_redirection(char *err)
{
	if (err)
	{
		ft_putstr_fd("error :", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	init_cmd_redir(t_utils *data, t_input *s, char *r)
{
	data->ptoken = list_index_token(s->clist, data->i_list - 1);
	data->ntoken = list_index_token(s->clist, data->i_list + 1);
	data->err_redir = NULL;
	if (data->ntoken)
	{
		data->cmd = cmd_index(s->cmd_list, data->i_cmd);
		data->tab = ft_split(data->ntoken->c, ' ');
		if (open_data(data, r) == -1)
			data->err_redir = ft_strjoin_free(data->tab[0], strerror(errno), 0, 0);
	}
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
		_cmd->err_redir = data->err_redir;
		ft_lstaddb_cmd(&s->cmd_list, _cmd);
	}
	if (*r == '>')
	{
		_cmd = cmd(0, data->file, *rest_args, data->i_cmd);
		_cmd->err_redir = data->err_redir;
		ft_lstaddb_cmd(&s->cmd_list, _cmd);
	}
	progress_list(data, s, *rest_args);	
}

char	*join_tab(char **tab, int j, int ftab)
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
	if (tab && ftab)
		free_tab(tab);
	return (t);
}

void	modify_redirection(t_utils *data, char *rest_args, char *r)
{
	if (*r == '<' && !data->err_redir)
		data->cmd->fdi = data->file;
	if (*r == '>' && !data->err_redir)
		data->cmd->fdo = data->file;
	data->cmd->err_redir = data->err_redir;
	if (data->ntoken)
		data->ptoken->next = data->ntoken->next;
	else
		data->ptoken->next = data->ntoken;
	if (rest_args)
		data->cmd->args = ft_strjoin_free(data->cmd->args, rest_args, 0, 1);
}
