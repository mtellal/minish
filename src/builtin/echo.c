/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:59:54 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/03 14:17:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	echo(char *args, char *n_args, t_input *s)
{
	if (args && args[0] == '$')
	{
		if (!ft_strcmp(args, "$?"))
			ft_putnbr_fd(get_last_status(), STDIN_FILENO);
		else
			write(1, "0", 1);
	}
	else
	{
		char	**str;
		char	*loc;
		int		i;

		i = 1;
		if (!s->value)
		{
		if ((str = ft_split(s->input, '\"')) && str[1])
		{
			puts("1");
			while (str[i])
			{
				ft_putstr_fd(str[i], 1);
				++i;
			}
		}
		else if ((str = ft_split(s->input, '\''))&& str[1])	
		{
			puts("2");
			while (str[i])
			{
				ft_putstr_fd(str[i], 1);
				++i;
			}
		}
		else if ((loc = (ft_strchr(s->input, '$'))) && loc)
		{
			puts("3");
			if (loc + 1 != NULL && !ft_isalpha(loc[1]))
				write(1, loc, ft_strlen(loc));
		}
		}
		else
		{
			ft_putstr_fd(args, 1);
		}
	}
	if (n_args)
		ft_putstr_fd(" ", 1);
}

int	print_args(char *args)
{
	int	i;

	 if (!ft_strncmp(args, "-n", 2))
	 {
		 i = 2;
		 while (args[i] && args[i] == 'n')
		 	i++;
		 if (!args[i])
			 return (0);
		 else
			 return (1);
	 }
	 else
		 return (1);
}

void	ft_echo(char **args, t_input *s)
{
	int	verif;
	int	i;
	int	sl;
	char	*loc;
	
	i = 1;
	sl = 1;
	verif = 0;
	while (args && args[i] && !print_args(args[i]))
	{
		i++;
		sl = 0;
	}
	while (args && args[i])
	{
		if (!ft_strncmp(args[i], "''", 2) || !ft_strncmp(args[i], "\"\"", 2))
		{
			free(args[i]);
			args[i] = ft_strdup("");
		}
		echo(args[i], args[i + 1], s);
		// int	o = 0;
		// while (s->input[o] && s->input[o] != '$' && s->input[o] != '\0')
		// 	++o;
		// while (s->input[o] != ' ' && s->input[o] != '\'' && s->input[o] != '\"' && s->input[o] != '\0')
		// 	++o;
		// write(1, s->input + o, ft_strlen(s->input + o));
		verif = 1;
		i++;
	}
	if ((loc = ft_strchr(s->input, '$')) && verif == 0)
	{
		if (*(loc + 1) == '\0' || *(loc + 1) == '\"' 
			|| *(loc + 1) == '\'')
			write(1, "$", 1);
		
	}
	if (sl)
		ft_putstr_fd("\n", 1);
	return (return_status(EXIT_SUCCESS, s));
}
