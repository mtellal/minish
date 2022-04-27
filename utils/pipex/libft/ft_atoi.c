/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:21:50 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:10:17 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			s = s * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		i = (10 * i) + (*nptr - '0');
		nptr++;
	}
	i = i * s;
	return (i);
}
