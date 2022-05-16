/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:03:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/16 09:45:59 by mtellal          ###   ########.fr       */
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

void	cmd_input(t_list *plist, t_list *list, t_list *nlist, t_input *s)
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
	}
	else if (plist)
	{
		// x < y args
		char *args = ft_strjoin_free(ptoken->c, rest_args, 0, 1);
		ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(infile, NULL, args, INPUT)));

	}
	list++;
}

void	command_table(t_list *list, t_input *s)
{
	t_token	*token;
	t_list	*plist;
	int	index_sep;

	index_sep = index_separator(list);
	token = list->content;
	if (index_sep == -1)
	{
		s->cmd_list = ft_lstnew(cmd(NULL, NULL, token->c, NOFILES));
		return ;
	}
	plist = NULL;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (*token->c == '<')
				cmd_input(plist, list, list->next, s);
		}
		plist = list;
		list = list->next;
	}
}
