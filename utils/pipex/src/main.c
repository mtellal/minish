/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:56:50 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/01 17:31:57 by mtellal          ###   ########.fr       */
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
	s->data.argc--;
	s->data.argv++;
}

/*
 *      verifier les opens avec le ft_open ( return int + message d'erreurs etc)
 */

void	ft_open_files(t_pip *s)
{
	t_data	data;
	int		in;
	int		out;
	char	*outfile;

	data = s->data;
	outfile = data.argv[data.argc - 1];
	if (!ft_strcmp(data.argv[1], "here_doc"))
	{
		open_heredoc(s, outfile);
	}
	else
	{
		s->hd = 0;
		in = ft_open(&s->fdi, data.argv[1], O_RDONLY, 0);
		if (in == -1)
			err("Error file\nError", 1);
		out = ft_open(&s->fdo, outfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (out == -1)
		{
			close(s->fdi);
			err("Error file\nError", 1);
		}
	}
}

void	init(t_pip *s, char **argv, int argc)
{
	s->arg = malloc(sizeof(int **) * (argc - 3));
	s->cmd = malloc(sizeof(int *) * (argc - 3));
	if (!s->cmd || !s->arg)
	{
		err("error in allocating t_pip", 0);
		close_files(s);
	}
	ft_pipe(argc - 4, s);
	fill_args(s, argv, (argc - 3));
	fill_commands(s, (argc - 3));
}

//      probleme 'awk "{$1++}"' ok mais probleme quote_split "awk 'xx'" 
//      unlink here_doc
//      faire plus de tests avec des fonctions plus complexes  

int	pipex(int argc, char **argv, char **env)
{
	t_pip	s;

	if (argc >= 5)
	{
		s.data.argc = argc;
		s.data.argv = argv;
		s.data.env = env;
		s.err.cmd = 0;
		s.err.args = 0;
		ft_open_files(&s);
		init(&s, s.data.argv, s.data.argc);
		processes(&s);
	}
	else
		err("Erreur: probleme d'arguments", 0);
	return (0);
}
