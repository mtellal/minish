/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 22:14:03 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_cmd	*cmd(int fdi, int fdo, char *args, int id)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdi = fdi;
	cmd->fdo = fdo;
	cmd->args = args;
	cmd->id = id;
	cmd->cmd = NULL;
	cmd->cmd_args = NULL;
	return (cmd);	
}

int	init_cmd_redir(t_utils *data, t_input *s, t_list *plist, t_list *nlist, int index, char *r)
{
	if (!nlist)
		return (-1);
	data->ntoken = nlist->content;
	if (plist)
		data->ptoken = plist->content;
	data->cmd = cmd_index(s->cmd_list, index);
	data->tab = ft_split(data->ntoken->c, ' ');
	open_data(data, r);
	return (0);
}

void	no_cmd(t_utils *data, t_input *s, t_list *plist, char **rest_args, char *r, int id_cmd)
{
	if (s->cmd_list)
		id_cmd = ft_lstsize(s->cmd_list);
	if (plist)
		*rest_args = ft_strjoin_free(data->ptoken->c, *rest_args, 0, 1);
	if (*r == '<')
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, *rest_args, id_cmd)));
	if (*r == '>')
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, *rest_args, id_cmd)));
}

void	modify_cmd(t_list *list, t_input *s, int i, int index)
{
	t_utils	*data;
	t_list	*plist;
	t_list *nlist;
	char	*rest_args;
	char	*r;

	data = ft_calloc(1, sizeof(t_utils));

	r = ((t_token*)list->content)->c;
	plist = list_index(s->clist, index - 1);	
	nlist = list_index(s->clist, index + 1);
	
	if (init_cmd_redir(data, s, plist, nlist, i, r) == -1)
		return ;
	rest_args = join_tab(data->tab, 1);
	if (data->cmd)
		modify_redirection(data, plist, nlist, rest_args, r);
	if (!data->cmd)
	{
		no_cmd(data, s, plist, &rest_args, r, i);
		if (!plist || (plist && data->ptoken->type == SEPARATOR))
                {
			if (plist)
				plist->next = nlist;
			else
				s->clist = nlist;
			data->ntoken->c = rest_args;
		}
		else if (plist)
		{
			data->ptoken->c = rest_args;
			plist->next = nlist->next;
		}
	}
}

/*
 *	degrouper les separator => err lorsque < x |> out	|> ou |< a separer
 */

void	cmd_redirections(t_list *list, t_input *s)
{
	t_token	*token;
	int		index;
	int		i;
	int		reset;

	i = 0;
	index = 0;
	while (list)
	{
		reset = 0;
		token = list->content;
		if (token->type == SEPARATOR && list->next)
		{
			if (*token->c == '<' || *token->c == '>')
			{
				modify_cmd(list, s, i, index);
				list = s->clist;
				i = 0;
				reset = 1;
				index = 0;
				s->nb_sep--;
			}
			else
				i++;
		}
		if (!reset)
		{
			index++;
			list = list->next;
		}
	}
}
