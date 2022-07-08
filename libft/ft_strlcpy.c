/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:53:21 by mtellal           #+#    #+#             */
/*   Updated: 2021/01/05 16:41:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (src)
		l = ft_strlen(src);
	if (!dst || !src)
		return (0);
	while (i + 1 < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (n != 0)
		dst[i] = '\0';
	return (l);
}
