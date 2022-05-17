/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/17 21:38:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_cmd	*cmd(int fdi, int fdo, char *args, enum s_options OPTION, int id)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdi = fdi;
	cmd->fdo = fdo;
	cmd->args = args;
	cmd->option = OPTION;
	cmd->id = id;
	return (cmd);	
}

enum s_options	sep_to_opt(char *s)
{
	if (!ft_strcmp(s, "<"))
		return (INPUT);
	if (!ft_strcmp(s, ">"))
		return (OUTPUT);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	return (NOFILES);
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

/*
 *	convertir les inputs x < y z et < y x z dans la cmd_list avec le fdi et fdo set
 *	+ modifie la clist pour que traiter correctement le reste des separateurs 
 */
	// PRONLEME RECREER UNE COMMANDE POUR ls < in < file

void	open_n_close(t_utils *data, int flags, mode_t mode, char r)
{
	if (r == '<' && data->cmd && data->cmd->fdi > 2)
		close(data->cmd->fdi);
	if (r == '>' && data->cmd && data->cmd->fdo > 2)
		close(data->cmd->fdo);
	if (ft_open(&data->file, data->tab[0], flags, mode) == -1)
	{
		ft_putstr_fd("err input file \n", 2);
		exit(0);
	}
}

void	cmd_redirection(t_list *plist, t_list *nlist, t_input *s, int index, char *r)
{
	t_utils	*data;
	char	*rest_args;

	data = ft_calloc(1, sizeof(t_utils));
	if (!nlist)
		return ;
	data->ntoken = nlist->content;
	if (plist)
		data->ptoken = plist->content;
	data->cmd = NULL;
	if (s->cmd_list && ft_lstsize(s->cmd_list) - 1 >= index)
		data->cmd = (t_cmd*)list_index(s->cmd_list, index)->content;

	data->tab = ft_split(data->ntoken->c, ' ');
	
	if (*r == '<')
		open_n_close(data, O_RDONLY, 0, '<');
	if (*r == '>')
		open_n_close(data, O_CREAT | O_RDWR | O_TRUNC, 0666, '>');

	rest_args = join_tab(data->tab, 1);
	if (data->cmd)
	{
		if (*r == '<')
			data->cmd->fdi = data->file;
		if (*r == '>')
			data->cmd->fdo = data->file;
		if (nlist)
			plist->next = nlist->next;
		else
			plist->next = nlist;
		if (rest_args)
			data->cmd->args = ft_strjoin_free(data->cmd->args, rest_args, 0, 1);	
	}
	if (!data->cmd)
	{
		if (!plist || (plist && data->ptoken->type == SEPARATOR))
                {
                        if (*r == '<')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args, INPUT, index)));
                        if (*r == '>')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, INPUT, index)));
			if (plist)
                                plist->next = nlist;
                        else
                                s->clist = nlist;
                        data->ntoken->c = rest_args;
                }
		else if (plist)
		{
			rest_args = ft_strjoin_free(data->ptoken->c, rest_args, 0, 1);
			if (*r == '<')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args, INPUT, index)));
			if (*r == '>')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, INPUT, index)));
			data->ptoken->c = rest_args;
			plist->next = nlist->next;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////



/*
 *	degrouper les separator => err lorsque < x |> out	|> ou |< a separer
 */

void	command_table(t_list *list, t_input *s)
{
	t_token	*token;
	t_list	*plist;
	int		i;
	int		reset;

	if (index_separator(list) == -1)
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, 1, ((t_token*)list->content)->c, NOFILES, 0)));
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
			if (*token->c != '<' && *token->c != '>')
				i++;
		}
		if (!reset)
		{
			plist = list;
			list = list->next;
		}
	}
	ft_putstr_fd("///////////////////////////////\n", 2);
	show_command_table(s);
	//show_cmd_list(s->cmd_list);
	layer2(s->clist, s);
}
