/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/29 16:50:29 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	initialise la struct t_input
 */

void	init_data_input(t_input *s, int argc, char **argv, char **env)
{
	s->argc = argc;
	s->argv = argv;
	s->f_env = env;
	s->input = NULL;
	s->tlist = NULL;
	s->llist = 0;
	s->clist = NULL;
	s->nb_sep = 0;
	s->nb_cmd = 0;
	s->cmd_list = NULL;
	s->nb_pipes = 0;
	s->pipes = NULL;
	s->env = NULL;
	ft_init(s, env);
	//show_env(s->env);
	//print_tab_env(s->env);
}

/*
 *	recupere l'input avec la readline lib
 *	si l'input != NULL => lexer et parser appele
 */

int	getInput(t_input *s)
{
	char	*buffer;
	int	i;
	void	(*clear_list)(void *s);

	i = 0;
	s->argv++;
	clear_list = &clear_telement;
	while ((buffer = readline(PROMPT)) != NULL)
	{
		if (*buffer)
			add_history(buffer);
		s->input = buffer;
		s->llist = ft_strlen(buffer);
		if (*buffer)
		{
			lexer(s);
			parser(s);
			ft_lstclear(&s->clist, clear_list);
		}
		i++;
		//free(buffer);
	}
	return (0);
}

int	input(t_input *si, int argc, char **argv, char **env)
{
	init_data_input(si, argc, argv, env);
	getInput(si);
	
	return (0);
}
