/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:08:05 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/24 10:39:24 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *mdf, const char *a, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!a[0])
		return ((char *)mdf);
	while (mdf[i] && i < n)
	{
		if (mdf[i + j] == a[j])
		{
			while (mdf[i + j] == a[j] && i + j < n && a[j])
				j++;
			if (a[j] == '\0')
				return ((char *)&mdf[i]);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
