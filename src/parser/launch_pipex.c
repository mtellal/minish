/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:44:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/11 17:58:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"


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
	}
	return (-1);
}

char	**argv_pipex(t_input *s)
{
        char    **tab;

	if (exist_separator(s->clist) < 0)
	{
		tab = malloc(sizeof(char*) * 3);
		if (!tab)
			return (NULL);
		tab[0] = "./pipex";
		tab[1] = ((t_token*)s->clist->content)->c;
		tab[2] = NULL;
	}
        /*int i = 0;
        printf("tab send to pipex\n");
        while (i < 3)
        {
                printf("%s      ", tab[i]);
                i++;
        }
        printf("\n");
	*/return (tab);
}



/*
 *	s->llist + 1 pour le ./pipex
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

