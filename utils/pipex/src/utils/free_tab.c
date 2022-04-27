/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:32:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/01/22 18:31:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **p)
{
	int	i;

	i = 0;
	while (p && p[i])
	{
		free(p[i]);
		i++;
	}
	if (p)
		free(p);
}
