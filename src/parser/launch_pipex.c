/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:44:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/12 15:18:30 by mtellal          ###   ########.fr       */
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

char	**cmd_and_args(t_input *s, int l)
{
	char	**tab;

	tab = ft_calloc(3, sizeof(char*));
	if (!tab)
		return (NULL);
	tab[0] = "./pipex";
	tab[1] = clist_to_s(s->clist, l);
	tab[2] = NULL;
	return (tab);
}

char	**argv_pipex(t_input *s)
{
        char    **tab;
	t_token	*token;
	int	i_sep;
	int	nb_cmd;

	i_sep = exist_separator(s->clist);
	nb_cmd = nb_token_type(s->clist, ALPHANUM);
	nb_cmd++;
	if (i_sep < 0)
		tab = cmd_and_args(s, s->llist);
	else
	{
		// determiner le separateur ; | < > 
		token  = ((t_token*)list_index(s->clist, i_sep)->content);
		token->type = SEPARATOR;
		if (!ft_strcmp(token->c, "|"))
		{
			
		}

	}
	/*
        int i = 0;
        printf("tab send to pipex\n");
        while (i < 3)
        {
                printf("'%s'      ", tab[i]);
                i++;
        }
        printf("\n");
	*/return (tab);
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
			pipex(s->llist + 1, argv, s->env, NOFILES);
	}
	wait(NULL);
}

