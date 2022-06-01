/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:58:46 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 20:36:38 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	modify_env(t_input *s)
{
	t_env	*n;
	char	*str;
	char	*buffer;

	n = NULL;
	buffer = NULL;
	close(s->p_env[1]);
	free_env(s);
	while ((buffer = get_next_line(s->p_env[0])))
	{
		str = ft_substr(buffer, 0, ft_strlen(buffer) - 1);
		n = str_to_env(str);
		ft_lstadd_back_env(&s->env, n);
	}
	close(s->p_env[0]);
}
