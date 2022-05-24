/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:39:14 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:39:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	char	*p;

	p = NULL;
	tab = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (tab == NULL)
		return (NULL);
	p = tab;
	while (s1 && *s1 != '\0')
		*tab++ = *s1++;
	while (s2 && *s2 != '\0')
		*tab++ = *s2++;
	*tab = '\0';
	return (p);
}
