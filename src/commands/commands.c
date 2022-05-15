/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:48:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 10:06:27 by mtellal          ###   ########.fr       */
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

int	init_argv(char ***argv)
{
	*argv = ft_calloc(2, sizeof(char*));
	if (!argv)
		return (0);
	*argv[0] = ft_strdup("./pipex");
	return (1);
}


/////////////////	verify is separator (| < > >> << ; &) correct //////////////////

void	merge_tokens(t_list *l1, t_list *l2)
{
	t_token *t1;
	t_token *t2;
	t_token *token;

	t1 = l1->content;
	t2 = l2->content;
	l1->content = ft_calloc(1, sizeof(t_token));
        token = l1->content;
	token->type = type_token(*(t1->c));
        token->c = ft_strjoin_free(t1->c, t2->c, 1, 1);
	l1->next = l2->next;
}

char	*swap_first(char **tab, int len)
{
	int	i;
	char	*t;

	i = 2;
	if (ft_strlen_tab(tab) < 2)
	{
		t = ft_strdup(tab[0]);
		free_tab(tab);
		return (t);
	}
	if (!tab || !*tab)
		return (NULL);
	t = ft_strjoin_free(tab[1], " ", 1, 0);
	t = ft_strjoin_free(t, tab[0], 1, 1);
	while (tab[i])
	{
		if (!t)
			t = ft_strjoin_free(t, tab[i], 0, 1);
		else
			t = ft_strjoin_free(t, tab[i], 1, 1);
		free(tab[i]);
		i++;
	}
	t[len] = '\0';
	free(tab);
	return (t);
}

void	order_clist(t_list *list, t_input *s)
{
	t_list	*plist;
	t_token *ptoken;
	t_list	*nlist;
	t_token	*token;

	plist = NULL;
	nlist = list->next;
	while (list)
	{
		token = list->content;
		if (plist)
			ptoken = plist->content;
		if (*token->c == '<' && nlist)
		{
			//	ls < Makefile || < ls Makefile
			if (plist && !err_cmd(ptoken->c, s))
			{	// ls < Makefile
				if (nlist->next)
				{
					merge_tokens(plist, nlist);
					free(token->c);
					free(token);		
					list = nlist->next;
				}
			}	
			else
			{	// <  Makefile ls
				if (plist)	
					plist->next = nlist;
				else
					s->clist = nlist;
				token = nlist->content;
				char **tab = ft_split(token->c, ' ');
				token->c = swap_first(tab, ft_strlen(token->c));
			}
		}
		plist = list;
		list = list->next;
		if (nlist)
			nlist = list->next;
	}
}


char	**clist_to_argv(t_input *s)
{
	t_token	*token;
	char		**argv;

	verify_separator(s->clist);
	if (s->nb_sep > 0)
		order_clist(s->clist, s);
	if (!init_argv(&argv))
		return (NULL);
	while (s->clist)
	{
		token = s->clist->content;
		if (token->type == SEPARATOR)
		{
			ft_putstr_fd("sep",2);
		}
		else
			argv = add_tab(argv, token->c);
		s->clist = s->clist->next;
	}
	int i = 0;
	while (i < ft_strlen_tab(argv))
	{
		printf("(%s) ", argv[i]);
		i++;
	}
	printf("\n");
	return (argv);
}
