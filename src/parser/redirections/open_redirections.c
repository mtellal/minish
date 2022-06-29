/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:19:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/29 09:30:04 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	set_options(char *r, int *flags, mode_t *mode)
{
	*flags = -1;
	*mode = 0666;
	if (!ft_strcmp(r, "<"))
	{
		*flags = O_RDONLY;
		*mode = 0;
	}
	if (!ft_strcmp(r, ">"))
		*flags = O_CREAT | O_RDWR | O_TRUNC;
	if (!ft_strcmp(r, ">>"))
		*flags = O_CREAT | O_RDWR | O_APPEND;
	if (*flags == -1)
		return (-1);
	return (0);
}

int	open_data(t_utils *data, char *r)
{
	int	flags;
	mode_t	mode;

	if (!set_options(r, &flags, &mode))
		return (open_n_close(data, flags, mode, r));
	else if (!ft_strcmp(r, "<<"))
		return (open_n_close_hd(data));
	return (0);
}

int	open_n_close(t_utils *data, int flags, mode_t mode, char *r)
{
	if (*r == '<' && data->cmd && data->cmd->fdi > 2)
		close(data->cmd->fdi);
	if (*r == '>' && data->cmd && data->cmd->fdo > 2)
		close(data->cmd->fdo);
	return (ft_open(&data->file, data->tab[0], flags, mode));
}
