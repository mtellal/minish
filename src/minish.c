/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/08 14:24:32 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_data(t_input *s, int argc, char **env)
{
	set_last_status(0);
	s->argc = argc;
	s->nb_sep = 0;
	s->nb_cmd = 0;
	s->nb_pipes = 0;
	s->hd = 0;
	s->pipes = NULL;
	s->input = NULL;
	s->tlist = NULL;
	s->clist = NULL;
	s->cmd = NULL;
	s->env = NULL;
	ft_init(s, env);
}

void	minishell(t_input *s)
{
	launch_parser(s);
	if (s->clist && !err_separator(s->clist, s))
	{
		launch_separators(s);
		launch_executer(s);
	}
	free_all(s, 0);
}

int	launch_minishell(t_input *s)
{
	char	*buffer;

	while (1)
	{
		signal(SIGINT, &sig_int);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline(PROMPT);
		if (!buffer)
			ctrl_d(s);
		if (*buffer)
			add_history(buffer);
		if (verif_pair_of_quotes(buffer) != -1)
		{
			s->input = ft_strdup(buffer);
			if (s->input && *s->input)
				minishell(s);
			else if (s->input)
				free(s->input);
		}
		free(buffer);
		buffer = NULL;
	}
	return (0);
}

int	init(t_input *s, int argc, char **env)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		||!isatty(STDERR_FILENO))
	{
		ft_putstr_fd("error tty stdin/stdout invalid\n", 2);
		exit(0);
	}
	init_data(s, argc, env);
	return (0);
}
