/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:03:26 by mtellal           #+#    #+#             */
/*   Updated: 2020/12/19 22:49:40 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t taille)
{
	size_t	i;

	i = 0;
	while (*dst && i < taille)
	{
		dst++;
		i++;
	}
	if (i == taille)
		return (i + ft_strlen(src));
	while (*src)
	{
		if (i < taille - 1)
			*dst++ = *src;
		src++;
		i++;
	}
	*dst = '\0';
	return (i + ft_strlen(src));
}
