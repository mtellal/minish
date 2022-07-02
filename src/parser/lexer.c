/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:58:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/01 18:45:02 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

enum s_type	type_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (SEPARATOR);
	return (ALPHANUM);
}

t_token	*token(char *c)
{
	t_token		*token;

	if (!c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type_token(*c);
	token->c = c;
	token->next = NULL;
	return (token);
}

void	lexer(t_input	*s)
{
	int			i;

	i = 0;
	while (s->input && s->input[i])
	{
		ft_lstaddb_token(&s->tlist, token(&s->input[i]));
		i++;
	}
}
