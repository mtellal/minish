/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:02:23 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/29 11:09:18 by mtellal          ###   ########.fr       */
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

	write(1, "heredoc> ", 9);
	ss = get_next_line(0);
	ss = ft_substr(ss, 0, ft_strlen(ss) - 1);
	if (!ss)
		write(2, "erreur gnl", 10);
	if (!ft_strcmp(ss, s->data.argv[2]))
		return (0);
	write(s->fdi, ss, ft_strlen(ss));
	write(s->fdi, "\n", 1);
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
	close(s->fdi);
	in = ft_open(&s->fdi, ".here_doc", O_RDONLY, 0);
	if (in == -1)
	{
		close(s->fdi);
		unlink(".here_doc");
		err("Error file\nError", 1);
	}
}
