/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:09 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:13:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ndigit(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	if (n >= 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		zero;
	long	o;

	o = (long)n;
	zero = ft_ndigit(o);
	tab = (char *)malloc(sizeof(char) * zero + 1);
	if (tab == NULL)
		return (NULL);
	if (o < 0)
	{
		tab[0] = '-';
		o *= -1;
	}
	tab[zero--] = '\0';
	if (n == 0)
		tab[zero] = '0';
	while (o > 0)
	{
		tab[zero--] = (unsigned char)((o % 10) + '0');
		o /= 10;
	}
	return (tab);
}
