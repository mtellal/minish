/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 21:08:16 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"


void	init_data_input(t_input *s, int argc, char **argv, char **env)
{
	s->argc = argc;
	s->argv = argv;
	s->env = env;
	s->input = NULL;
	s->tlist = NULL;
	s->llist = 0;
	s->clist = NULL;
}

int	getInput(t_input *s)
{
	char	*buffer;
	int	i;
	void	(*clear_tlist)(void *s);

	i = 0;
	s->argv++;
	clear_tlist = &clear_telement;
	while ((buffer = readline(PROMPT)) != NULL)
	{
		if (*buffer)
			add_history(buffer);
		s->input = buffer;
		s->llist = ft_strlen(buffer);
		if (*buffer)
		{
			lexer(s);
			show_token_list(s);
			printf("number of groups: %i\n",number_of_groups(s->tlist));
			parser(s);
			show_command_table(s);
			ft_lstclear(&s->tlist, clear_tlist);
			ft_lstclear(&s->clist, clear_tlist);
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
