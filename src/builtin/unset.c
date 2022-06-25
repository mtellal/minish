/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/23 17:09:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_env	*previous_already_exists(t_env *n, t_env *env)
{
	t_env	*penv;

	penv = NULL;
	while (env)
	{
		if (!ft_strcmp(env->var, n->var) && penv)
			return (penv);
		penv = env;
		env = env->next;
	}
	return (NULL);
}

int	lst_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	free_tenv(t_env *e)
{
	if (!e)
		return ;
	if (e->var)
		free(e->var);
	if (e->content)
		free(e->content);
	free(e);
}

int	msg_err_unset(char *tab)
{
	ft_putstr_fd("error: unset: << ", 2);
	ft_putstr_fd(tab, 2);
	ft_putstr_fd(" >> : invalid id\n", 2);
	return (-1);
}

int	verif_args(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!isalnum(tab[i][j]))
				return (msg_err_unset(tab[i]));
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_unset(char **args, t_input *s)
{
	int		i;
	t_env	*n;
	t_env	*pe;
	t_env	*sub;
	t_env	*r;

	n = NULL;
	pe = NULL;
	r = s->env;
	i = 1;
	if (verif_args(args) != -1)
	{
		while (args && args[i])
		{
			n = str_to_env(args[i]);
			pe = previous_already_exists(n, s->env);
			if (pe)
			{
				sub = n->next;
				pe->next = sub;
				free_tenv(n);
			}
			i++;
		}
	}
	s->env = r;
	env_to_pipe(s->env, s->p_env);
	exit(EXIT_SUCCESS);
}
