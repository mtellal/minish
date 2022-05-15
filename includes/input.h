/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/15 12:56:22 by mtellal          ###   ########.fr       */
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
	EXPAND,
	SEPARATOR,
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
	
	// option pour pipex (pipe ou input ou output etc)
	enum s_options	option;

	int		nb_sep;
	int		nb_cmd;
	int		nb_expand;

}		t_input;


//////////		I N P U T . C		//////////

int	input(t_input *s, int argc, char **argv, char **env);
int	getInput(t_input *s);
void	init_sinput(t_input *s, int argc, char **argv, char **env);


/////////////////////////////////////////////////////////
//			L E X E R		       //
/////////////////////////////////////////////////////////

//////////		L E X E R . C		//////////

void    clear_telement(void     *s);
t_token *token(char *c);
enum s_type     type_token(char c);
void	lexer(t_input *s);
void	clear_telement(void *s);




/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

//////////		P A R S E R . C		//////////

char    *tlist_to_s(t_list      *list, int l);
void    parser(t_input *s);
int     number_of_groups(t_list *list);

//////////		U T I L S 		//////////

/////	P A R S E R _ U T I L S .C 	/////

t_list	*list_index(t_list *list, int l);

/////	V E R I F Y _ S E PA  R T O R . C 	/////

int     ft_belong(char *s, char c);
int     same_char(char *s, char c, int l);
int     valid_separator(char    *s, int *err_sep);
int     msg_err_separator(char *s, int err_sep);
int     err_separator(t_list *list, t_input *s);

/////		U T I L S . C 		/////

int	ft_strlen_tab(char **tab);
void	free_tab(char **tab);
int	only_space(char *s);
int	index_separator(t_list *list);
int     nb_token_type(t_list *list, enum s_type type);

/////	L I S T _ U T I L S . C 	/////

void    clear_space(t_list *list, t_input *s);


/////	O R D E R _ C L I S T . C	/////

void    order_input(t_list *list, t_input *s);

/////////////////////////////////////////////////////////
//               C O M M A N D S . C         	       //
/////////////////////////////////////////////////////////

//////////	C O M M A N D S . C		//////////

char	**clist_to_argv(t_input *s);

//////////	L A U N C H _ P I P E X . C	//////////

void    launch_pipex(t_input *s);

//////////	I S _ C O M M A N D . C 	//////////

int	is_valid_cmd(char *cmd, t_input *s);
int     err_cmd(char    *cmd, t_input *s);

//////////		U T I L S		//////////

int     ft_strlen_tab(char **tab);
void    free_tab(char **tab);
int     index_separator(t_list *list);
int     nb_token_type(t_list *list, enum s_type type);




/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

//////////		L E X E R		//////////

void	show_token_list(t_input *s);

//////////		P A R S E R		//////////

void	show_command_table(t_input *s);

#endif
