/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:58:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/03 18:49:38 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

enum s_type	type_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (SEPARATOR);
	return (ALPHANUM);
}

t_token	*token(char *c, char quote)
{
	t_token		*token;

	if (!c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (quote)
		token->type = ALPHANUM;
	else
		token->type = type_token(*c);
	token->c = c;
	token->next = NULL;
	return (token);
}

void	lexer(t_input	*s)
{
	int			i;
	char	quote;

	i = 0;
	quote = 0;
	while (s->input && s->input[i])
	{
		if (quote && quote == s->input[i] && ft_belong("'\"", s->input[i]))
			quote = 0;
		else if (!quote && ft_belong("'\"", s->input[i]))
			quote = s->input[i];
		ft_lstaddb_token(&s->tlist, token(&s->input[i], quote));
		i++;
	}
}
