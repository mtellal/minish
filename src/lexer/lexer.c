/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:58:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 17:09:42 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	free pointer de void
 *	utilise pour clear la liste chainee
 */

void	clear_telement(void	*s)
{
	free(s);
}

/*
 *	determine un s_type selon un char
 *	utilise pour les s_token par le lexer + parser
 */

enum s_type	type_token(char c)
{
	if (c == '$')
		return (EXPAND);
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&' || c == ' ')
		return (SEPARATOR);
	return (ALPHANUM);
}

/*
 *	retourne un token malloce
 *	selon son type et son char 
 *	token = c => char / type => enum s_type
 */

t_token	*token(char *c)
{
	t_token	*token;

	if (!c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type_token(*c);
	token->c = c; 
	return (token);
}


/*
 *	transforme chaque caractere en un token (type,char)
 *	et l'ajoute a la liste chainee tlist (tokelist)
 *	(show_tokens_lists montre les differents tokens + situee dans /utils/debug/lexer)
 */

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
	//show_token_list(s);
	//printf("number of groups: %i\n",number_of_groups(s->tlist));
}
