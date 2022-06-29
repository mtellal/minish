/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/09 17:30:52 by mtellal          ###   ########.fr       */
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

void	progress_list(t_utils *data, t_input *s, char *rest_args)
{
	if (!data->ptoken || (data->ptoken && data->ptoken->type == SEPARATOR))
	{
		if (data->ptoken)
			data->ptoken->next = data->ntoken;
		else
			s->clist = data->ntoken;
		data->ntoken->c = rest_args;
	}
	else if (data->ptoken)
	{
		data->ptoken->c = rest_args;
		data->ptoken->next = data->ntoken->next;
	}
}

void	modify_io_cmd(t_token *list, t_input *s, int i_cmd, int i_list)
{
	t_utils	*data;
	char	*rest_args;
	char	*r;

	data = ft_calloc(1, sizeof(t_utils));
	r = list->c;
	data->i_cmd = i_cmd;
	data->i_list = i_list;
	init_cmd_redir(data, s, r);
	rest_args = join_tab(data->tab, 1, 0);
	if (data->cmd)
		modify_redirection(data, rest_args, r);
	if (!data->cmd)
		add_cmd(data, s, &rest_args, r);
}

void	redir_match(t_coor *c, t_input *s, t_token **list, int *reset)
{
	if (ft_belong("<>", *((*list)->c)))
	{
		modify_io_cmd(*list, s, c->i, c->j);
		*list = s->clist;
		c->i = 0;
		*reset = 1;
		c->j = 0;
		s->nb_sep--;
	}
	else
		c->i++;
}

void	cmd_redirections(t_token *token, t_input *s)
{
	t_token	*list;
	t_coor	c;
	int		reset;

	c.i = 0;
	c.j = 0;
	list = token;
	while (list)
	{
		reset = 0;
		if (list->type == SEPARATOR && list->next)
			redir_match(&c, s, &list, &reset);
		if (!reset)
		{
			c.j++;
			list = list->next;
		}
	}
}