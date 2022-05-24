/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:30:38 by mtellal           #+#    #+#             */
/*   Updated: 2021/11/23 18:26:37 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nmot(char const *s, char c)
{
	int				m;
	char const		*a;

	m = 0;
	a = s;
	while (*a != '\0')
	{
		if (*a != c)
		{
			m++;
			while (*a != c && *(a + 1) != '\0')
				a++;
		}
		a++;
	}
	return (m);
}

static int	ft_nlettre(char const *s, char c)
{
	int				l;
	char const		*a;

	l = 0;
	a = s;
	while (*a == c && *a != '\0')
		a++;
	while (*a != c && *a++ != '\0')
		l++;
	return (l);
}

static char	*ft_clean(char **t, int i)
{
	while (i > 0)
	{
		free(t[i]);
		i--;
	}
	free(t);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	char	*tab;
	int		i;

	i = 0;
	t = (char **) malloc(sizeof(char *) * (ft_nmot(s, c) + 1));
	if (!s || t == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			tab = (char *) malloc(sizeof(char) * ft_nlettre(s, c) + 1);
			if (!tab)
				return ((char **)ft_clean(t, i));
			ft_strlcpy(tab, s, ft_nlettre(s, c) + 1);
			*t++ = tab;
			i++;
			while (*s != c && *(s + 1) != '\0')
				s++;
		}
		s++;
	}
	*t = 0;
	return (t - i);
}
