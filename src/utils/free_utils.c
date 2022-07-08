/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:00:11 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/08 16:53:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ctrl_d(t_input *s)
{
	ft_putstr_fd("\nexit\n", 1);
	free_all(s, 1);
	exit(EXIT_SUCCESS);
}

void	ft_lstclear_parser(t_token **list)
{
	t_token	*token;

	while (*list)
	{
		if ((*list)->c)
			free((*list)->c);
		token = *list;
		*list = (*list)->next;
		free(token);
	}
	*list = NULL;
}

void	ft_lstclear_lexer(t_token **list)
{
	int		i;
	t_token	*ft;

	i = 0;
	while (*list)
	{
		if ((*list)->c)
			free((*list)->c);
		i++;
		ft = *list;
		*list = (*list)->next;
		free(ft);
	}
	*list = NULL;
}

void	free_pipes(t_input *s)
{
	int	i;

	i = 0;
	if (!s->pipes)
		return ;
	while (s->pipes && s->pipes[i])
	{
		free(s->pipes[i]);
		i++;
	}
	free(s->pipes);
	s->pipes = NULL;
}

void	free_all(t_input *s, int env)
{
	ft_lstclear_lexer(&s->tlist);
	ft_lstclear_parser(&s->clist);
	if (s->cmd)
		clear_cmd_list(&s->cmd);
	if (s->pipes)
	{
		close_pipes(s->pipes, s->nb_pipes);
		free_pipes(s);
	}
	if (env && s->env)
	{
		free_env(&s->env);
		rl_clear_history();
	}
	if (s->hd)
		unlink(".heredoc");
}
