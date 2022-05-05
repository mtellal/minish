/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getInput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:56:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/04/26 15:15:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	getInput(t_input *s)
{
	char	*buffer;
	int	i;

	i = 0;
	s->argv++;
	while ((buffer = readline(PROMPT)) != NULL)
	{
		if (*buffer)
			add_history(buffer);
		i++;
		free(buffer);
	}
	return (0);
}
