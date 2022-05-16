/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/16 18:34:22 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_cmd	*cmd(char *fdi, char *fdo, char *args, enum s_options OPTION)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdi = fdi;
	cmd->fdo = fdo;
	cmd->args = args;
	cmd->option = OPTION;
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

void	cmd_input(t_list *plist, t_list *nlist, t_input *s)
{
	t_token *ntoken;
	t_token *ptoken;
	char	**tab;
	char	*infile;
	char	*rest_args;

	if (!nlist)
		return ;
	ntoken = nlist->content;
	if (plist)
		ptoken = plist->content;
	tab = ft_split(ntoken->c, ' ');
	infile = ft_strdup(tab[0]);
	rest_args = join_tab(tab, 1);
	if (!plist || (plist && ptoken->type == SEPARATOR))
	{
		//	< file ls
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(infile, NULL, rest_args, INPUT)));
		s->clist = nlist;
		ntoken->c = rest_args;
	}
	else if (plist)
	{
		// x < y args
		char *args = ft_strjoin_free(ptoken->c, rest_args, 0, 1);
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(infile, NULL, args, INPUT)));
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
		if (!ft_strcmp(ss, cmd->args))
			index = i;
		l = l->next;
		i++;
	}
	if (index == -1)
		return (NULL);
	else
		return (list_index(s->cmd_list, index)->content);
}


void	cmd_output(t_list *plist, t_list *nlist, t_input *s, char last_sep)
{
	t_cmd	*c;
	t_token *ptoken;
	t_token *ntoken;

	char	**tab;
	char	*outfile;
	char	*rest_args;

	if (!nlist)
		return ;
	c = NULL;
	ptoken = NULL;
	ntoken = nlist->content;
	if (plist)
	{
		ptoken = plist->content;	
		c = is_cmd_existing(ptoken->c, s);
	}
	tab = ft_split(ntoken->c, ' ');
        outfile = ft_strdup(tab[0]);
        rest_args = join_tab(tab, 1);
        if (!plist || (plist && ptoken->type == SEPARATOR))
        {
                //      > file ls
		if (!c || (last_sep != '<' && last_sep != '>' && !c->fdi))
                	ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(NULL, outfile, rest_args, OUTPUT)));
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
                if (!c || (last_sep != '>' && last_sep != '<'))
			ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(NULL, outfile, args, OUTPUT)));
		else
			c->fdo = outfile;
		ptoken->c = args;
                plist->next = nlist->next;
        }
}

void	command_table(t_list *list, t_input *s)
{
	t_token	*token;
	t_list	*plist;
	int	index_sep;
	char	last_sep;

	index_sep = index_separator(list);
	token = list->content;
	if (index_sep == -1)
	{
		s->cmd_list = ft_lstnew(cmd(NULL, NULL, token->c, NOFILES));
		return ;
	}
	plist = NULL;
	last_sep = 0;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (*token->c == '<')
			{
				cmd_input(plist, list->next, s);
				list = s->clist;
			}
			if (*token->c == '>')
			{
				cmd_output(plist, list->next, s, last_sep);
				list = s->clist;
			}
			/*ft_putchar_fd(*token->c, 2);
			ft_putstr_fd("  ", 2);
			show_command_table(s);
			show_cmd_list(s->cmd_list);
			*/last_sep = *token->c;
		}
		plist = list;
		list = list->next;
	}
}
