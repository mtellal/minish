/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 16:25:25 by mtellal          ###   ########.fr       */
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
	s->env = env;
	s->input = NULL;
	s->tlist = NULL;
	s->llist = 0;
	s->clist = NULL;
	s->nb_sep = 0;
	s->nb_cmd = 0;
	s->cmd_list = NULL;
	s->nb_pipes = 0;
	s->pipes = NULL;
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
		//	!!!!!	>> a ne pas add dans l'histo	!!!!
		//	verifier si d'autres execptions

		if (*buffer)
			add_history(buffer);
		s->input = buffer;
		s->llist = ft_strlen(buffer);
		if (*buffer && err_quotes(buffer, &s->input) != -1)
		{
			ft_putstr_fd("input : ", 2);
			ft_putstr_fd(s->input, 2);
			ft_putstr_fd("\n", 2);
			lexer(s);
			parser(s);
			//ft_lstclear(&s->tlist, clear_list);
			ft_lstclear(&s->clist, clear_list);
		}
		i++;
		free(buffer);
	}
	return (0);
}

int	input(t_input *si, int argc, char **argv, char **env)
{
	init_data_input(si, argc, argv, env);
	getInput(si);
	
	return (0);
}
