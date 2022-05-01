/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:02:23 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/01 16:43:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	error_input(t_pip *s)
{
	int	in;

	in = ft_open(&s->fdi, ".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (in == -1)
	{
		close(s->fdi);
		err("error file\nError", 1);
	}
	return (in);
}

int	here_doc(t_pip *s)
{
	char	*ss;
	char	*line;

	write(1, "heredoc> ", 9);
	ss = get_next_line(0);
	line = ft_substr_free(ss, 0, ft_strlen(ss) - 1, 1);
	if (!ss)
	{
		free(line);
		write(2, "erreur gnl", 10);
	}
	if (!ft_strcmp(line, s->data.argv[2]))
	{
		free(line);
		return (0);
	}
	write(s->fdi, line, ft_strlen(line));
	write(s->fdi, "\n", 1);
	free(line);
	return (1);
}

void	get_input(t_pip *s)
{
	int		in;

	in = error_input(s);
	while (1)
	{
		if (!here_doc(s))
			break ;
	}
	get_next_line(s->fdi);
	close(s->fdi);
	in = ft_open(&s->fdi, ".here_doc", O_RDONLY, 0);
	if (in == -1)
	{
		close(s->fdi);
		unlink(".here_doc");
		err("Error file\nError", 1);
	}
}
