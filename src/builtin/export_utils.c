/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:58:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 18:44:45 by mtellal          ###   ########.fr       */
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
