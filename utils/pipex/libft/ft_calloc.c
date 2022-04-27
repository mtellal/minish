/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:10:44 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/24 10:40:21 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	void	*p;
	size_t	l;

	l = (nmemb * size);
	tab = (char *) malloc(l);
	if (tab == NULL)
		return (NULL);
	p = (void *)tab;
	while (l > 0)
	{
		*tab++ = 0;
		l--;
	}
	return (p);
}
