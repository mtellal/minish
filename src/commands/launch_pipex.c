/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:44:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 10:51:10 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	renvoie le nombre de token du type 'type' dans la liste
 */

int     nb_token_type(t_list *list, enum s_type type)
{
        int     i;
        t_token *token;

        i = 0;
        while (list)
        {
                token = list->content;
                if (token->type == type)
                        i++;
                list = list->next;
        }
        return (i);
}

/*
 *	verifie s'il y a un separateur dans une liste
 *	et renvoie son index
 *	utile pour isoler les cmd
 */

int	exist_separator(t_list *list)
{
	int	i;
	t_token	*token;

	i = 0;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR)
			return (i);
		list = list->next;
		i++;
	}
	return (-1);
}

/*
 *	paracours s-clist jusqu'a l
 *	et transforme les tokens en char*
 *	ex: ls -la [f] => 
 */

char	**cmd_to_pipex(t_token *token, int pipex)
{
	char	**tab;
	int		i;

	i = 0;
	if (pipex)
		tab = ft_calloc(3, sizeof(char*));
	else
		tab = ft_calloc(2, sizeof(char*));
	if (!tab)
		return (NULL);
	if (pipex)
		tab[i++] = "./pipex";
	tab[i++] = token->c;
	tab[i] = NULL;
	return (tab);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);	
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**add_argv(char **t, char *s)
{
	int	lt;
	char	**tab;
	int	i;

	i = 0;
	lt = ft_strlen_tab(t);
	tab = ft_calloc(lt + 2, sizeof(char*));
	if (!tab)
		return (NULL);
	while (i < lt)
	{
		tab[i] = ft_strdup(t[i]);
		free(t[i]);
		i++;
	}
	tab[i++] = s;
	tab[i] = NULL;
	free(t);
	return (tab);
}

int	len_type(t_list *list, enum s_type type)
{
	int	len;
	t_token	*token;

	len = 0;
	while (list)
	{
		token = list->content;
		if (token->type == type)
			len += ft_strlen(token->c);
		list = list->next;
	}
	return (len);
}

char	**argv_pipex(t_input *s)
{
	return (NULL);
}



/*
 *	s->llist + 1 pour le ./pipex
 *	parse la clist et la transforme en char** pour l'**argv de pipex
 *	lance un processus et dans le fils exe pipex 
 *	je fork parceque pipex se termine tout seul
 */

void	launch_pipex(t_input *s)
{
	pid_t	t;
	char	**argv;

	argv = argv_pipex(s);
	if (argv)
	{	
		t = fork();
		if (t == -1)
		{
			ft_putstr_fd("Error fork", 2);
			exit(0);
		}
		if (t == 0)
			pipex(ft_strlen_tab(argv), argv, s->env, s->option);
	}
	wait(NULL);
}

