/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:58:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/01/26 21:20:17 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup( char *s)
{
	unsigned char	*tab;
	unsigned char	*t;

	if (!s)
		return (NULL);
	tab = (unsigned char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (tab == NULL)
		return (NULL);
	t = tab;
	while (*s != '\0')
	{
		*tab++ = *s++;
	}
	*tab = '\0';
	return ((char *)t);
}
