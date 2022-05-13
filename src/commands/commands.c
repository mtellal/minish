/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:48:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 17:35:03 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	RESUME
 *	
 *	un token de clist est au format : "xxx xx x" ou "|&;>"
 *
 *	1 - Ce balader dans la clist (ou un token est plusieurs caracteres du meme type) 
 *	ensuite verifier si le prenier mot du token de clist est une cmd valide, 
 *	- si oui alors les jetons alphanum suivants sont des args pour cette commande alors
 *	empaqueter la commande et ses args au formant pipex (./pipex "cmd args")
 *	- si non message d'erreur + gestion des leaks/msg d'erreurs
 *	
 *	2 - 
 *
 */

char	*tokens_to_char(t_list *list, int l)
{
	int	i;
	t_token	*token;
	char	*tab;

	i = 0;
	tab = NULL;
	while (list && i < l)
	{
		token = list->content;
		if (token->type != SEPARATOR)
		{
			if (!tab)
				tab = ft_strdup(token->c);
			else
				tab = ft_strjoin_free(tab, ft_strjoin(" ",token->c), 1, 1);	
		}
		list = list->next;
		i++;
	}
	return (tab);
}

int	init_argv(char ***argv)
{
	*argv = ft_calloc(2, sizeof(char*));
	if (!argv)
		return (-1);
	*argv[0] = ft_strdup("./pipex");
	return (1);
}

void	free_token(void *token)
{
	t_token	*t;

	t = (t_token*)token;
	free(t->c);
	free(t);
}

void	rm_first_link(t_list *list, t_list *plist)
{
	t_token	*token;

	token = list->content;
	plist->next = list->next;
	free(token->c);
	free(token);
}

void	swap_first(t_list *list)
{
	t_list	*alist;
	t_list	*blist;
	t_list	*clist;
	t_token	*token;

	alist = list->next;
	blist = alist->next;
	clist = blist->next;
	alist->next = clist;
	blist->next = alist;
	token = list->content;
	free(token->c);
	free(token);
}

/*
 *	savoir si le carac '<' existe en un seul exemplaire dans char*
 *
 */

int	only_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] == ' ')
		i++;
	if (s[i] != c)
		return (i);
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0' && s[i] != c)
		return (i);
	else
		return (-1);
}

void	order_clist(t_list *list)
{
	t_token	*token;
	t_list	*plist;
	int	i;

	i = 0;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (only_char(token->c, '<') == -1)
			{
				//	ex:	"< Makefile ls" | "ls < Makefile"
				if (i > 0)
				{
					// cas "ls < Makefile" alors rendre "ls Makefile"
					//ft_lstdelone(list, free_token);
					rm_first_link(list, plist);
				}
				else
				{	
					swap_first(list);
				}
			}
			else
				ft_putstr_fd("error: parser token <", 2);
		}
		plist = list;
		list = list->next;
		i++;
	}
}

void	clist_to_cmd(t_input *s)
{
	t_token	*token;
	int		index_sep;
	char		**argv;

	order_clist(s->clist);
	index_sep = index_separator(s->clist);
	if (init_argv(&argv) == -1)
		return ;
	while (s->clist)
	{
		token = s->clist->content;
		printf("%s ", token->c);
		index_sep = index_separator(s->clist);
		/*if (token->type != SEPARATOR && err_cmd(token->c, s))
			return ;
		*/if (index_sep == -1)
		{
			argv = add_tab(argv, tokens_to_char(s->clist, s->llist));	
			break ;
		}
		else
			argv = add_tab(argv, tokens_to_char(s->clist, index_sep));
		if (index_sep != -1)
			s->clist = list_index(s->clist, index_sep + 1);
		else
			s->clist = s->clist->next;
	}
}
