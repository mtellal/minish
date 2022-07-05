/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:03:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:32:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_cmd_redir(t_utils *data, t_input *s, char *r)
{
	reset_stdin();
	data->ptoken = list_index_token(s->clist, data->i_list - 1);
	data->ntoken = list_index_token(s->clist, data->i_list + 1);
	data->err_redir = NULL;
	if (data->ntoken)
	{
		data->cmd = cmd_index(s->cmd, data->i_cmd);
		if (data->cmd)
			data->err_redir = data->cmd->err_redir;
		data->tab = quote_split(data->ntoken->c);
		if (!data->err_redir && open_data(data, r) == -1)
		{
			data->err_redir = ft_strjoin(data->tab[0], " :");
			data->err_redir = ft_strjoin_free(data->err_redir,
					strerror(errno), 1, 0);
		}
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
		ft_lstaddb_cmd(&s->cmd, _cmd);
	}
	if (*r == '>')
	{
		_cmd = cmd(0, data->file, *rest_args, data->i_cmd);
		_cmd->err_redir = data->err_redir;
		ft_lstaddb_cmd(&s->cmd, _cmd);
	}
	progress_list(data, s, *rest_args);
}

void	modify_redirection(t_utils *data, char *rest_args, char *r)
{
	if (*r == '<' && !data->err_redir)
		data->cmd->fdi = data->file;
	if (*r == '>' && !data->err_redir)
		data->cmd->fdo = data->file;
	if (data->err_redir)
		data->cmd->err_redir = data->err_redir;
	if (data->ntoken)
	{
		data->ptoken->next = data->ntoken->next;
		free_token(&data->ntoken);
	}
	else
		data->ptoken->next = data->ntoken;
	if (rest_args)
		data->cmd->args = ft_strjoin_free(data->cmd->args, rest_args, 1, 1);
	free_token(&data->list);
}
