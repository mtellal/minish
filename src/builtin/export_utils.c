/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:58:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/02 10:40:35 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	ft_print_error1(char *str)
{
	write(2, "export: '", 9);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

void	env_to_pipe(t_env *env, int *pipe)
{
	close(pipe[0]);
	while (env)
	{
		write(pipe[1], env->var, ft_strlen(env->var));
		write(pipe[1], "=", 1);
		write(pipe[1], env->content, ft_strlen(env->content));
		write(pipe[1], "\n", 1);
		env = env->next;
	}
	close(pipe[1]);
}

void	update_env(t_input *s)
{
	t_env	*n;
	char	*str;
	char	*buffer;

	n = NULL;
	buffer = NULL;
	close(s->p_env[1]);
	free_env(s);
	while (1)
	{
		buffer = get_next_line(s->p_env[0]);
		if (!buffer)
			break ;
		str = ft_substr(buffer, 0, ft_strlen(buffer) - 1);
		n = str_to_env(str);
		ft_lstadd_back_env(&s->env, n);
	}
	close(s->p_env[0]);
}

int	ft_str_valid(char *str)
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
