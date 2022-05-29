/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:31:35 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/29 22:26:05 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//	identifier valide = alnum ou '_'

int ft_valid_char(char c)
{
    if (ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

void    ft_print_error1(char *str)
{
    write(2, "export: '", 9);
    write(2, str, ft_strlen(str));
    write(2, "': not a valid identifier\n", 26);
}

int ft_str_valid(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		if (!ft_valid_char(str[i]))
		{
			ft_print_error1(str);
			return (0);
		}
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			ft_putstr_fd("error: syntax error near unexpected token '('\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void    ft_export(char **args, t_input *s)
{
	ft_putstr_fd("/////////////// export ///////////////\n", 2);
	int	i;
	t_env	*n;
	t_env	*r;

	r = s->env;
	i = 1;
	if (args && !args[i])
	{
		while (s->env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(s->env->var, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(s->env->content, 1);
			ft_putstr_fd("\"\n", 1);
			s->env = s->env->next;
		}
	}
	while (args && args[i])
	{
		if (ft_str_valid(args[i]))
		{
			n = str_to_env(args[i]);
			ft_lstadd_back_env(&s->env, n);
		}
		i++;
	}
	s->env = r;
	exit(EXIT_SUCCESS);
}

