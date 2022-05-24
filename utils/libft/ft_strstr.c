/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:56:34 by mtellal           #+#    #+#             */
/*   Updated: 2020/12/21 14:45:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *meule_de_foin, const char *aiguille)
{
	char	*a;
	size_t	i;

	a = (char *)aiguille;
	i = 0;
	if (*aiguille == '\0')
		return ((char *)meule_de_foin);
	while (*meule_de_foin != '\0')
	{
		while (*meule_de_foin == *aiguille && *aiguille != '\0')
		{
			i++;
			aiguille++;
			meule_de_foin++;
		}
		if (i == ft_strlen(a) && *aiguille == '\0')
			return ((char *)(meule_de_foin - i));
		meule_de_foin -= i;
		aiguille -= i;
		i = 0;
		meule_de_foin++;
	}
	return (NULL);
}
