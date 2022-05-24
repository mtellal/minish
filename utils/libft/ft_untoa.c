/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:20:18 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:38:58 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ndigit(unsigned long n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_untoa(unsigned int n)
{
	char			*tab;
	unsigned int	zero;
	unsigned long	o;

	o = (unsigned long)n;
	zero = ft_ndigit(o);
	tab = (char *)malloc(sizeof(char) * zero + 1);
	if (tab == NULL)
		return (NULL);
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
