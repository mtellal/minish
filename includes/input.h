/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/12 14:09:52 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"
#include "pipex.h"

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "



typedef struct s_list	t_list;

//////////		L E X E R		//////////

enum s_type
{
	ALPHANUM,
	BRACKET,
	EXPAND,
	SEPARATOR,
	QUOTE,
};

typedef struct s_token
{
	enum s_type	type;
	char		*c;
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
	
	// longueur de la list selon lexer ou parser
	int		llist;

	// command table used by parser
	struct s_list	*clist;

}		t_input;


//////////		I N P U T . C		//////////

int	input(t_input *s, int argc, char **argv, char **env);

int	getInput(t_input *s);

void	init_sinput(t_input *s, int argc, char **argv, char **env);


/////////////////////////////////////////////////////////
//			L E X E R		       //
/////////////////////////////////////////////////////////

//////////		L E X E R . C		//////////

enum s_type     type_token(char c);

void	lexer(t_input *s);

void	clear_telement(void *s);


/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

//////////		P A R S E R . C		//////////

char    *tlist_to_s(t_list      *list, int l);

void	parser(t_input *s);

int	number_of_groups(t_list	*list);

//////////	P A R S E R _ U T I L S . C	//////////

t_list	*list_index(t_list *list, int i);

char	**argv_pipex(t_input *s);

char    *clist_to_s(t_list *list, int l);

//////////	L A U N C H _ P I P E X . C	//////////

void    launch_pipex(t_input *s);

/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

//////////		L E X E R		//////////

void	show_token_list(t_input *s);

//////////		P A R S E R		//////////

void	show_command_table(t_input *s);

#endif
