/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:53:30 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:17:04 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*c1;
	unsigned const char	*c2;

	c1 = s1;
	c2 = s2;
	while (n--)
	{
		if (*c1 != *c2)
		{
			return (*c1 - *c2);
		}
		c1++;
		c2++;
	}
	return (0);
}
