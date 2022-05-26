/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/24 18:03:25 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "



typedef struct s_list	t_list;

//////////		L E X E R		//////////

enum s_type
{
	ALPHANUM,
	SEPARATOR,
};

typedef struct s_token
{
	enum s_type	type;
	char		*c;
}		t_token;

//////////		P A R S E R		//////////

typedef struct s_cmd
{
	int		id;
	char		*args;
	int		fdi;
	int		fdo;
	char		**cmd_args;
	char		*cmd;

}		t_cmd;

typedef struct s_utils
{
	int	fdi;
	int	fdo;
	int	index;

	int	file;

	char	**tab;

	t_list	*list;
	t_list	*plist;
	t_list	*nlist;
	
	t_token	*token;
	t_token	*ptoken;
	t_token	*ntoken;
	
	t_cmd	*cmd;
}		t_utils;

/////////////////////////////////////////////////////////
//                      I N P U T                      //
/////////////////////////////////////////////////////////

typedef struct s_input
{
	int	argc;
	char	**argv;
	char	**env;

	char	*input;

	// tokens list used by lexer / content => t_token (c = char, type = alphanum | separator)
	struct s_list	*tlist;
	
	// longueur de la list selon lexer ou parser / content => t_token (c = cmd/mot, type an/sep)
	int		llist;

	// command list used by command list / 
	struct s_list	*clist;

	// list chainee de t_cmd 
	// content => t_cmd = (args = args, fdi, fdo, p_option = NOFILES, OUTPUT etc..)	
	struct s_list	*cmd_list;

	int		nb_sep;
	int		nb_cmd;

	int		nb_pipes;
	int		**pipes;
	int		hd;
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

//////////	C O M M A N D S . C 		//////////

t_cmd   *cmd(int fdi, int fdo, char *args, int id);
char    *join_tab(char **tab, int j);
void	command_table(t_list *list, t_input *s);

void    show_cmd_list(t_list *list);
void    clear_cmd_list(t_list *list, t_input *s);

//////////	L A Y E R 2 . C 		//////////

t_cmd   *cmd_index(t_list *list, int index);
void    layer2(t_list *list, t_input *s);



//////////		Q U O T E S		//////////

// > parser/quotes

/////	V E R I F _ Q U O T E S . C 		/////

int     index_quote(char *s, char c);
int     wrong_number_quote(char *s);
char    *clear_quotes(char *s);
int     msg_err_quote(void);
int     err_quotes(char *buffer, char **input);

/////	M O D I F Y . Q U O T E S . C 		/////

int     modify_quotes(t_list *list);

/////	E X P A N D _ Q U O T E S . C 		/////

char    *expand_quotes(char *s);

/////	Q U O T E _ U T I L S . C 		/////

int     last_quote_in_word(char *s, char quote, char p_quote);
int     first_quote_in_word(char *s, int index, char quote, char p_quote);





//////////		U T I L S 		//////////

/////	P A R S E R _ U T I L S .C 	/////

t_list	*list_index(t_list *list, int l);

/////	V E R I F Y _ S E P A R T O R . C 	/////

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











/////////////////////////////////////////////////////////
//               E X E C U T E R  . C                  //
/////////////////////////////////////////////////////////

/////	E X E C U T E R .C 		/////

void    executer(t_list *list, t_input *s);

/////	P I P E S . C			/////

void    set_pipes(t_list *list, t_input *s);

/////	V E R I F Y _ C O M M A N D S . C /////

char    **tab_path(char **env);
int     valid_cmd(char *path, char *cmd);
char    *is_valid_cmd(char *cmd, char **env);






/////////////////////////////////////////////////////////
//               C O M M A N D S . C         	       //
/////////////////////////////////////////////////////////

//////////	C O M M A N D S . C		//////////

void    open_n_close(t_utils *data, int flags, mode_t mode, char *r);

char	**clist_to_argv(t_input *s);

//////////	L A U N C H _ P I P E X . C	//////////

void    launch_pipex(t_input *s);

//////////	I S _ C O M M A N D . C 	//////////

int     err_cmd(char    *cmd, t_input *s);

//////////		U T I L S		//////////

int     ft_strlen_tab(char **tab);
void    free_tab(char **tab);
int     index_separator(t_list *list);
int     nb_token_type(t_list *list, enum s_type type);



/////////////////////////////////////////////////////////
//                      U T I L S                      //
/////////////////////////////////////////////////////////

/////	TAB_UTILS.C

char    **add_tab(char **tab, char *s);
char    *tab_to_s(char **tab);
int     ft_strlen_tab(char **tab);
void    free_tab(char **tab);

/////	STRING_UTILS.C

int     ft_belong(char *s, char c);

/////	OPEN_UTILS.C

int	ft_open(int *fd, char *file, int flags, mode_t mode);

/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

//////////		L E X E R		//////////

void	show_token_list(t_input *s);

//////////		P A R S E R		//////////

void	show_command_table(t_input *s);

#endif
