/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/31 17:49:06 by mtellal          ###   ########.fr       */
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
	s->p_env = NULL;
	ft_init(s, env);
	//show_env(s->env);
	//print_tab_env(s->env);
}

/*
 *	si l'input != NULL => lexer et parser appele
 */

int	getInput(t_input *s)
{
	char	*buffer;
	int	i;

	i = 0;
	s->argv++;
	while (1)
	{
		signal(SIGINT, &sig_int);
		buffer = readline(PROMPT);
		if (!buffer)
		{
			ft_putstr_fd("ctrl-d triggered\n", 1);
			exit(0);
		}

		add_history(buffer);
		s->input = buffer;
		s->llist = ft_strlen(buffer);
		if (*buffer)
		{
			lexer(s);
			parser(s);
			ft_lstclear(&s->clist, &clear_telement);
		}
		i++;
		//free(buffer);
	}
	return (0);
}

int	input(t_input *s, int argc, char **argv, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("error tty stdin invalid\n", 2);
		exit(0);
	}
	signal(SIGINT, &sig_int);
	init_data_input(s, argc, argv, env);
	getInput(s);
	
	return (0);
}
