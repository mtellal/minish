/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:06:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/02/07 15:33:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*s;
	char	*d;

	if (!dest && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	n -= 1;
	if (s < d)
	{
		while ((int)n >= 0)
		{
			d[n] = s[n];
			n--;
		}
	}
	else
	{
		while ((int)n-- >= 0)
			*d++ = *s++;
	}
	return (dest);
}
