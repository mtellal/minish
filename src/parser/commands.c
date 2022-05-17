/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/17 15:26:27 by mtellal          ###   ########.fr       */
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

void	cmd_input(t_list *plist, t_list *nlist, t_input *s, int index)
{
	t_token *ntoken;
	t_token *ptoken;
	char	**tab;
	int	infile;
	char	*rest_args;

	if (!nlist)
		return ;
	ntoken = nlist->content;
	if (plist)
		ptoken = plist->content;
	
	tab = ft_split(ntoken->c, ' ');

	/*if (infile > 2)
	       close(infile);	
	*/
	if (ft_open(&infile, tab[0], O_RDONLY, 0) == -1)
	{
		//	mieux gerer les erreurs
		ft_putstr_fd("err input file \n", 2);
		exit(0);
	}

	rest_args = join_tab(tab, 1);
	if (!plist || (plist && ptoken->type == SEPARATOR))
	{
		//	< file ls
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(infile, 1, rest_args, INPUT, index)));
		if (!plist)
			s->clist = nlist;
		else
			plist->next = nlist;
		ntoken->c = rest_args;
	}
	else if (plist)
	{
		// x < y args
		char *args = ft_strjoin_free(ptoken->c, rest_args, 0, 1);
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(infile, 1, args, INPUT, index)));
		ptoken->c = args;
		plist->next = nlist->next;
	}
}
//////////////////////////////////////////////////////////////////

t_cmd	*is_cmd_existing(char *ss, t_input *s)
{
	t_cmd	*cmd;
	int	i;	
	int	index;
	t_list *l;

	i = 0;
	index = -1;
	if (!ss)
		return (NULL);
	l = s->cmd_list;
	while (l)
	{
		cmd = l->content;
		if (cmd->args && !ft_strcmp(ss, cmd->args))
			index = i;
		l = l->next;
		i++;
	}
	if (index == -1)
		return (NULL);
	else
		return (list_index(s->cmd_list, index)->content);
}


void	cmd_output(t_list *plist, t_list *nlist, t_input *s, char last_sep, int index)
{
	t_cmd	*c;
	t_token *ptoken;
	t_token *ntoken;

	char	**tab;
	int	outfile;
	char	*rest_args;

	if (!nlist)
		return ;
	c = NULL;
	ptoken = NULL;
	ntoken = nlist->content;
	if (plist)
	{
		ptoken = plist->content;	
		if (s->cmd_list && ptoken->type == ALPHANUM)
			c = is_cmd_existing(ptoken->c, s);
	}
	tab = ft_split(ntoken->c, ' ');
	if (c && c->fdo > 2)
		close(c->fdo);
        if (ft_open(&outfile, tab[0], O_RDONLY, 0) == -1)
        {
                //      mieux gerer les erreurs
                ft_putstr_fd("err output file \n", 2);
                exit(0);
        }

        rest_args = join_tab(tab, 1);
        if (!plist || (plist && ptoken->type == SEPARATOR))
        {
                //      > file ls
		if (!c || (last_sep != '<' && last_sep != '>' && !c->fdi))
                	ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(1, outfile, rest_args, OUTPUT, index)));
		else
		{
			// ouvrir et fermer pour trunc
			c->fdo = outfile;
		}
		s->clist = nlist;
                ntoken->c = rest_args;
        }
        else if (plist)
        {
                // x < y args
                char *args = ft_strjoin_free(ptoken->c, rest_args, 0, 1);
                if (!c || (last_sep != '>' && last_sep != '<' && ptoken->type == SEPARATOR))
			ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(1, outfile, args, OUTPUT, index)));
		else
			c->fdo = outfile;
		ptoken->c = args;
                plist->next = nlist->next;
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
	char	last_sep;
	int		i;
	int		reset;

	if (index_separator(list) == -1)
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, 1, token->c, NOFILES, 0)));
	plist = NULL;
	last_sep = 0;
	i = -1;
	while (list)
	{
		reset = 0;
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (*token->c == '<')
			{
				cmd_input(plist, list->next, s, i);
				list = s->clist;
				i = 0;
				reset = 1;
			}
			if (*token->c == '>')
			{
				cmd_output(plist, list->next, s, last_sep, i);
				list = s->clist;
				i = 0;
				reset = 1;
			}
			last_sep = *token->c;
		}
		else
			i++;
		if (!reset)
		{
			plist = list;
			list = list->next;
		}
	}
	ft_putstr_fd("///////////////////////////////\n", 2);
	show_command_table(s);
	//show_cmd_list(s->cmd_list);
	//	layer2(s->clist, s);
}
