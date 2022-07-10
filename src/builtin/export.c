/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:31:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 11:39:58 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	set_env_var(char *args, t_input *s)
{
	t_env	*e;
	t_env	*n;

	n = str_to_env(args);
	e = var_exists(n->var, s->env);
	if (e)
	{
		if (!n->equal)
		{
			free_env(&n);
			return ;
		}
		if (!e->equal)
			e->equal = 1;
		if (e->content)
			free(e->content);
		e->content = ft_strdup(n->content);
		free_env(&n);
	}
	else if (n)
		ft_lstadd_back_env(&s->env, n);
}

char	**sort_env(t_env *lenv)
{
	int		i;
	int		ltab;
	char	**tab;
	char	*swap;

	i = 0;
	tab = env_to_tab(lenv);
	ltab = ft_strlen_tab(tab);
	while (tab && tab[i] && i < ltab)
	{
		if (i + 1 < ltab && (ft_strcmp(tab[i], tab[i + 1]) > 0))
		{
			swap = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = swap;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}

void	print_export(t_input *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = sort_env(s->env);
	while (tab && tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	free_tab(tab);
}

int	valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '=')
		return (0);
	while (s && s[i] && s[i] != '=')
	{
		if (!isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args, t_input *s)
{
	int		i;
	int		err_status;
	t_env	*r;

	r = s->env;
	i = 1;
	err_status = EXIT_SUCCESS;
	if (args && !args[i])
		print_export(s);
	while (args && args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			err_status = EXIT_FAILURE;
		}
		else
			set_env_var(args[i], s);
		i++;
	}
	s->env = r;
	return (return_status(err_status, s));
}
