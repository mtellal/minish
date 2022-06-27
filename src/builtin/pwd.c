/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:02:24 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 11:45:35 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_pwd(int i, t_input *s)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		if (i)
			set_var_value("PWD", cwd, s);
		else
			ft_putendl_fd(cwd, 1);
	}
	else
	{
		perror("pwd");
		exit(EXIT_FAILURE);
	}
	if (s->nb_cmd > 1)
		exit(EXIT_SUCCESS);
}
