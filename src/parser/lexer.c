/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:58:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/03 13:46:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	clear_telement(void	*s)
{
	free(s);
}

enum s_type	type_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (SEPARATOR);
	return (ALPHANUM);
}

t_token	*set_token(int nb_quote, char *c, t_token *token)
{
	if (nb_quote > 0)
		token->type = ALPHANUM;
	else if (!nb_quote)
		token->type = type_token(*c);
	token->c = c;
	token->next = NULL;
	return (token);
}

t_token	*token(char *c)
{
	t_token		*token;
	static char	quote = 0;
	static int	nb_quote = 0;

	if (!c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (quote && *c == quote)
	{
		nb_quote++;
		if (nb_quote == 2)
			nb_quote = 0;
	}
	if (!quote && ft_belong("'\'''\"'", *c))
	{
		quote = *c;
		nb_quote++;
	}
	return (set_token(nb_quote, c, token));
}

void	lexer(t_input	*s)
{
	int	i;

	i = 0;
	while (s->input && s->input[i])
	{
		ft_lstaddb_token(&s->tlist, token(&s->input[i])); 
		i++;
	}
	//show_token_list(s);
}
