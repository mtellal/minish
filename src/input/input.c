/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/05 17:55:29 by mtellal          ###   ########.fr       */
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
}

int	getInput(t_input *s)
{
	char	*buffer;
	int	i;

	i = 0;
	s->argv++;
	while ((buffer = readline(PROMPT)) != NULL)
	{
		if (*buffer)
			add_history(buffer);
		s->input = buffer;
		lexer(s);
		show_token_list(s);
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
