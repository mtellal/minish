/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:25:50 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/06 17:50:39 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	err_msg_redirection(char *err)
{
	if (err)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	free_utils_data(t_utils *data)
{
	if (data->ntoken)
		free_tab(data->tab);
	free(data);
}
