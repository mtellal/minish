/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 16:28:20 by mtellal          ###   ########.fr       */
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

void	open_n_close(t_utils *data, int flags, mode_t mode, char *r)
{
	if (*r == '<' && data->cmd && data->cmd->fdi > 2)
		close(data->cmd->fdi);
	if (*r == '>' && data->cmd && data->cmd->fdo > 2)
		close(data->cmd->fdo);
	if (ft_open(&data->file, data->tab[0], flags, mode) == -1)
	{
		ft_putstr_fd("err input file \n", 2);
		exit(0);
	}
}

void	modify_redirection(t_utils *data, t_list *plist, t_list *nlist, char *rest_args, char *r)
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

void	open_n_close_hd(t_utils *data)
{
	char	*buffer;

	if (data->cmd && data->cmd->fdi > 2)
		close(data->cmd->fdi);
	data->file = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (data->file == -1)
	{
		ft_putstr_fd("err open .heredoc", 2);
		exit(0);
	}
	while ((buffer = readline("heredoc> ")))
	{
		if (!ft_strcmp(buffer, data->tab[0]))
		{
			free(buffer);
			break ;
		}
		buffer = ft_strjoin_free(buffer, "\n", 1, 0);
		ft_putstr_fd(buffer, data->file);
		free(buffer);
	}
	close(data->file);
	data->file = open(".heredoc", O_RDONLY, 0);
	if (data->file == -1)
	{
		ft_putstr_fd("err open .heredoc", 2);
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
	
	if (!ft_strcmp(r, "<"))
		open_n_close(data, O_RDONLY, 0, r);
	if (!ft_strcmp(r, ">"))
		open_n_close(data, O_CREAT | O_RDWR | O_TRUNC, 0666, r);
	if (!ft_strcmp(r, ">>"))
		open_n_close(data, O_CREAT | O_RDWR | O_APPEND, 0666, r);
	if (!ft_strcmp(r, "<<"))
		open_n_close_hd(data);

	rest_args = join_tab(data->tab, 1);
	if (data->cmd)
		modify_redirection(data, plist, nlist, rest_args, r);
	if (!data->cmd)
	{
		if (!plist || (plist && data->ptoken->type == SEPARATOR))
                {
			//	< file cmd args   ||  | < file cmd args
			//	> file cmd args   ||  | > file cmd args
                        
			if (*r == '<')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args,index)));
                        if (*r == '>')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, index)));
			if (plist)
                                plist->next = nlist;
                        else
                                s->clist = nlist;
                        data->ntoken->c = rest_args;
                }
		else if (plist)
		{
			//	cmd < file args
			//	cmd > file args

			rest_args = ft_strjoin_free(data->ptoken->c, rest_args, 0, 1);
			if (*r == '<')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(data->file, 1, rest_args, index)));
			if (*r == '>')
				ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, data->file, rest_args, index)));
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
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, 1, ((t_token*)list->content)->c, 0)));
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
	//ft_putstr_fd("///////////// R E D I R E C T I O N //////////////////\n", 2);
	//show_command_table(s);
	//show_cmd_list(s->cmd_list);
	layer2(s->clist, s);
}