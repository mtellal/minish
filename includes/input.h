/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/05 19:17:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "

typedef struct s_list	t_list;

//////////		L E X E R		//////////

enum s_type
{
	ALPHANUM,
	REDIRECTION,
	BRACKET,
	PIPE, 
	EXPAND,
	SEPARATOR,
	QUOTE,
	ARITHMETIC,
	OTHER
};

typedef struct s_token
{
	enum s_type	type;
	char		c;
}		t_token;


//////////////////////////////////////////////////////////

typedef struct s_input
{
	int	argc;
	char	**argv;
	char	**env;

	char	*input;

	struct s_list	*tlist;
}		t_input;


//////////		I N P U T . C		//////////

int	input(t_input *s, int argc, char **argv, char **env);

int	getInput(t_input *s);

void	init_sinput(t_input *s, int argc, char **argv, char **env);


/////////////////////////////////////////////////////////
//			L E X E R		       //
/////////////////////////////////////////////////////////

//////////		L E X E R . C		//////////

void	lexer(t_input *s);



/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

//////////		L E X E R		//////////

void	show_token_list(t_input *s);

#endif
