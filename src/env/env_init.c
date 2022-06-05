/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:54:13 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 10:09:22 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_init(t_input *s, char **envp)
{
	t_env	*n;
	int		i;

	i = 0;
	n = NULL;
	while (envp && envp[i])
	{
		n = str_to_env(envp[i]);
		ft_lstadd_back_env(&s->env, n);
		i++;
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *n)
{
	t_env	*r;

	if (!n)
		return ;
	if (!lst || !*lst)
		*lst = n;
	else
	{
		r = *lst;
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = n;
		*lst = r;
	}
}

int	equal_index(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	return (i);
}

t_env	*str_to_env(char *str)
{
	t_env	*n;
	int		equal;

	if (!str)
		return (NULL);
	n = ft_calloc(1, sizeof(t_env));
	if (!n)
		return (NULL);
	equal = equal_index(str);
	n->len = ft_strlen(str);
	n->var = ft_substr(str, 0, equal);
	if (str[equal] && str[equal + 1])
		n->content = ft_substr(str + equal, 1, ft_strlen(str));
	else
		n->content = ft_strdup("");
	n->next = NULL;
	return (n);
}

void	show_env(t_env	*env)
{
	t_env	*r;

	r = env;
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd(env->var, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(env->content, 2);
		ft_putstr_fd("\n", 2);
		env = env->next;
	}
	env = r;
}
