/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:54:08 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/05 11:06:48 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	err_pipe(t_token *list, t_token *plist, t_token *nlist)
{
	int	err;

	err = 0;
	if (!plist || plist->type != ALPHANUM)
		err = 1;
	if (!nlist)
		err = 1;
	if (ft_strlen(list->c) > 1 && list->c[1] == '|')
		err = 1;
	if (err)
		return (msg_err_separator(list->c, 0));
	return (0);
}

int	match_sep(t_token *list, t_token *plist, t_input *s)
{
	int	err;

	err = 0;
	if (ft_lstsize_token(s->clist) == 1)
		return (msg_err_separator(list->c, 0));
	if (ft_belong("><", *list->c))
		err = err_redi(list, list->next);
	if (*list->c == '|' )
		err = err_pipe(list, plist, list->next);
	if (err)
		return (err);
	return (0);
}

int	err_separator(t_token *list, t_input *s)
{
	int		err;
	t_token	*r;
	t_token	*plist;

	plist = NULL;
	r = list;
	err = 0;
	while (list)
	{
		if (list->type == SEPARATOR)
		{
			err = match_sep(list, plist, s);
			if (err)
				return (err);
		}
		plist = list;
		list = list->next;
	}
	list = r;
	return (0);
}
