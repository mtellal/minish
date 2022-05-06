/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:58:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 17:38:56 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	clear_telement(void	*s)
{
	free(s);
}

enum s_type	type_token(char c)
{
	if (ft_isalnum(c))
		return (ALPHANUM);
	if (c == '<' || c == '>')
		return (REDIRECTION);
	if (c == '(' || c == ')' || c == '{' || c == '}')
		return (BRACKET);
	if (c == '|')
		return (PIPE);
	if (c == '$')
		return (EXPAND);
	if (c == ';')
		return (SEPARATOR);
	if (c == '\'' || c == '\"')
		return (QUOTE);
	if (c == '+' || c == '=' || c == '-' || c == '*' || c == '/' || c == '%')
		return (ARITHMETIC);
	return (OTHER);
}

t_token	*token(char *c)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type_token(*c);
	token->c = c; 
	return (token);
}

void	lexer(t_input	*s)
{
	int	i;

	i = 0;
	while (s->input && s->input[i])
	{
		if (!s->tlist)
			s->tlist = ft_lstnew(token(&s->input[i]));
		else
			ft_lstadd_back(&s->tlist, ft_lstnew(token(&s->input[i])));
		i++;
	}
}
