/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/06 15:03:17 by mtellal          ###   ########.fr       */
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


/////////////////////////////////////////////////////////
//                      I N P U T                      //
/////////////////////////////////////////////////////////

typedef struct s_input
{
	int	argc;
	char	**argv;
	char	**env;

	char	*input;

	// tokens list used by lexer
	struct s_list	*tlist;
	int		llist;

	// command table used by parser
	char		**table;

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

void	clear_telement(void *s);


/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

//////////		P A R S E R . C		//////////

void	parser(t_input *s);

int	number_of_groups(t_list	*list);

//////////	P A R S E R _ U T I L S . C	//////////

t_list	*tlist_index(t_list *list, int i);


/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

//////////		L E X E R		//////////

void	show_token_list(t_input *s);

//////////		P A R S E R		//////////

void	show_command_table(t_input *s);

#endif
