/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:42:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/01 15:06:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	 print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_putchar_fd('[', 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(']', 1);
		ft_putstr_fd("	'", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putendl_fd("'", 1);
		i++;
	}
}
