/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:31:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/29 16:52:14 by mtellal          ###   ########.fr       */
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
		e->content = ft_strdup(n->content);
		if (n->var)
			free(n->var);
		if (n->content)
			free(n->content);
		free(n);
	}
	else if (n)
		ft_lstadd_back_env(&s->env, n);
}

char	**sort_env(t_env *lenv)
{
	int	ltab;
	char	**tab;
	char	*swap;
	int	i;

	i = 0;
	tab = env_to_tab(lenv);
	ltab = ft_strlen_tab(tab);
	while (i < ltab)
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
	char	**tab;
	int	i;

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

void	ft_export(char **args, t_input *s)
{
	int		i;
	t_env	*r;

	r = s->env;
	i = 1;
	if (args && !args[i])
		print_export(s);
	if (args[i] && !ft_isalpha(args[i][0]))
	{
		write(2, "export: `", 9);
		write(2, args[i], ft_strlen(args[i]));
		write(2, "': not a valid identifier\n", 26);
		return (return_status(EXIT_FAILURE, s));
	}
	while (args && args[i])
	{
		set_env_var(args[i], s);
		i++;
	}
	s->env = r;
	return (return_status(EXIT_SUCCESS, s));
}
