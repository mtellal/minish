/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:02:19 by mtellal           #+#    #+#             */
/*   Updated: 2021/01/04 11:26:19 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	l;
	char			c;

	if (n < 0)
	{
		l = -n;
		write(fd, "-", 1);
	}
	else
		l = n;
	if (l >= 10)
		ft_putnbr_fd((l / 10), fd);
	l %= 10;
	c = l + '0';
	write(fd, &c, 1);
}
