/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:59:14 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:41:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		tab = (char *)malloc(sizeof(char));
		if (!tab)
			return (NULL);
		*tab = '\0';
		return (tab);
	}
	tab = (char *)malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, (s + start), len + 1);
	return (tab);
}
