/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:48:28 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/14 20:40:45 by mtellal          ###   ########.fr       */
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


/////////////////////	functions verify separator	/////////////////

int	ft_belong(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//	verifie si l char dans s sont bien c, utile pour << et >>	

int	same_char(char *s, char c, int l)
{
	int	i;

	i = 0;
	while (s[i] == c && i < l)
		i++;
	if (i == l)
		return (-1);
	return (i);
}

//	verifie si les separateurs (| > < >> << & ;) sont bien respectes

int	valid_separator(char	*s, int *err_sep)
{
	int	l;
	char	*tab;

	tab = "|<>&;";
	l = ft_strlen(s);
	*err_sep = 0;
	if (l == 2)
	{
		if (s[0] == '<')
			*err_sep = same_char(s, '<', 2);
		else if (s[0] == '>')
			*err_sep = same_char(s, '>', 2);
	}
	else if (ft_belong(tab, s[0]))
	{
		if (s[1] == '\0')
			*err_sep = -1;
		else
			*err_sep = 1;
	}
	return (*err_sep);
}

int	err_separator(char *s, int err_sep)
{
		ft_putstr_fd("error: syntax token '", 2);
		ft_putchar_fd(s[err_sep], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
}

int	verify_separator(t_list *list)
{
	t_token *token;
	int	err_sep;

	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR)
		{
			if (valid_separator(token->c, &err_sep) != -1)
				return (err_separator(token->c, err_sep));
		}
		list = list->next;
	}
	return (0);
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
		if (*token->c == '<')
		{
			//	ls < Makefile || < ls Makefile
			if (plist && !err_cmd(ptoken->c, s))
			{	// ls < Makefile
				if (nlist)
				{
					merge_tokens(plist, nlist);
					free(token->c);
					free(token);		
					list = nlist->next;
				}
			}	
			else
			{	// <  Makefile ls
				plist->next = nlist;
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
