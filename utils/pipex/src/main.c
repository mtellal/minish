/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:56:50 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/11 12:32:37 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_heredoc(t_pip *s, char *outfile)
{
	int	out;

	s->hd = 1;
	out = ft_open(&s->fdo, outfile, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (out == -1)
		err("Err file\Err", 1);
	get_input(s);
}

void	open_infile(t_pip *s)
{
	t_data	data;
	int	in;

	data = s->data;
	in = ft_open(&s->fdi, data.argv[1], O_RDONLY, 0);
	if (in == -1)
		err("Error file\nError", 1);
}

void	open_outfile(t_pip *s)
{
	t_data	data;
	int	out;
	char	*outfile;
	int	flags;

	data = s->data;
	outfile = data.argv[data.argc - 1];
	if (s->option == OUTPUT)
		flags = O_CREAT | O_RDWR | O_TRUNC;
	else
		flags = O_CREAT | O_RDWR | O_APPEND;
	out = ft_open(&s->fdo,  outfile, flags, 0666);
	if (out == -1)
	{
		close(s->fdi);
		err("Error file\nError", 1);
	}
}

/*
 *      verifier les opens avec le ft_open ( return int + message d'erreurs etc)
 */

void	ft_open_files(t_pip *s)
{
	t_data	data;

	data = s->data;
	s->fdi = 0;
	s->fdo = 1;
	if (s->option == INPUT)
		open_infile(s);
	if (s->option == OUTPUT || s->option == APPEND)
		open_outfile(s);
	if (s->option == NONE)
	{
		if (!ft_strcmp(data.argv[1], "here_doc"))
			open_heredoc(s, data.argv[data.argc - 1]);
		else
		{
			s->hd = 0;
			open_infile(s);
			open_outfile(s);
		}
	}
	if (s->option == HEREDOC)
		open_heredoc(s, data.argv[1]);
}

int	nb_cmd(enum s_options option, int argc, t_pip *s)
{
	if (option == NOFILES)
		return (argc - 1);
	if (option == NONE)
	{
		if (s->hd == 1)
			return (argc - 4);
		return (argc - 3);
	}
	if (option == HEREDOC)
		return (argc - 3);
	return (argc - 2);
}

int	pos_cmd(enum s_options option, t_pip *s)
{
	if (option == NOFILES || option == OUTPUT || option == APPEND)
		return (1);
	if (option == HEREDOC || s->hd == 1)
		return (3);
	return (2);
}

void	init(t_pip *s, char **argv, int argc)
{
	s->err.cmd = 0;
	s->err.args = 0;
	s->nb_cmd = nb_cmd(s->option, argc, s);
	s->nb_pipes = s->nb_cmd - 1;
	s->pos_cmd = pos_cmd(s->option, s);
	s->arg = malloc(sizeof(char **) * s->nb_cmd);
	s->cmd = malloc(sizeof(char *) * s->nb_cmd);
	if (!s->cmd || !s->arg)
	{
		err("error in allocating t_pip", 0);
		close_files(s);
	}
	ft_pipe(s->nb_pipes, s);
	fill_args(s, argv, s->nb_cmd);
	fill_commands(s, s->nb_cmd);
}

void	bad_arguments(int argc, int opt)
{
	if (argc < 2 || (opt == NONE && argc < 5))
		err("Error: bad arguments", 0);
	if (opt != NOFILES && argc < 3)
		err("Error: bad arguments", 0);
}

//      probleme 'awk "{$1++}"' ok mais probleme quote_split "awk 'xx'" 
//      unlink here_doc
//      faire plus de tests avec des fonctions plus complexes  

int	pipex(int argc, char **argv, char **env, int opt)
{
	t_pip	s;

	bad_arguments(argc, opt);
	s.data.env = env;
	s.option = opt;
	s.data.argv = argv;
	s.data.argc = argc;
	ft_open_files(&s);
	init(&s, argv, argc);
	processes(&s);
	return (0);
}
