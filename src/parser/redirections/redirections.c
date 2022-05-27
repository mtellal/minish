/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/27 16:39:58 by mtellal          ###   ########.fr       */
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

void	no_cmd(t_utils *data, t_input *s, t_list *plist, char **rest_args, int index, char *r)
{
	if (plist)
		*rest_args = ft_strjoin_free(data->ptoken->c, *rest_args, 0, 1);
	if (*r == '<')
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, *rest_args, index)));
	if (*r == '>')
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, *rest_args, index)));
}

void	cmd_redirection(t_list *plist, t_list *nlist, t_input *s, int index, char *r)
{
	t_utils	*data;
	char	*rest_args;

	data = ft_calloc(1, sizeof(t_utils));
	if (init_cmd_redir(data, s, plist, nlist, index, r) == -1)
		return ;
	rest_args = join_tab(data->tab, 1);
	if (data->cmd)
		modify_redirection(data, plist, nlist, rest_args, r);
	if (!data->cmd)
	{
		no_cmd(data, s, plist, &rest_args, index, r);
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

void	redirections(t_list *list, t_input *s)
{
	t_token	*token;
	t_list	*plist;
	int		i;
	int		reset;

	plist = NULL;
	i = 0;
	while (list)
	{
		reset = 0;
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (*token->c == '<' || *token->c == '>')
			{
				cmd_redirection(plist, list->next, s, i, token->c);
				list = s->clist;
				i = 0;
				reset = 1;
			}
		//	if (*token->c != '<' && *token->c != '>')
			else
				i++;
		}
		if (!reset)
		{
			plist = list;
			list = list->next;
		}
	}
}
