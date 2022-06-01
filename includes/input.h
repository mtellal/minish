/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 22:30:12 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "
#define PATH_MAX 4096


typedef struct s_list	t_list;

//////////		S _ L E X E R		//////////

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

//////////		S _ P A R S E R		//////////

typedef struct s_cmd
{
	int		id;
	char		*args;
	int		fdi;
	int		fdo;
	char		**cmd_args;
	char		*cmd;

}		t_cmd;

//////////		S _ E N V 			//////////

typedef struct s_env
{
	char	*var;
	char	*content;
	int		len;
	struct s_env	*next;

}		t_env;

//////////		S _ U T I L S 		//////////

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
	char	**f_env;

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

	struct s_env	*env;

	int		*p_env;
	int		lstatus;

}		t_input;


/////	minish.c

void	init_data(t_input *s, int argc, char **argv, char **env);
void	minishell(t_input *s);
int	input(t_input *s);
int	launch(t_input *s, int argc, char **argv, char **env);


/////	lexer.c

void	clear_telement(void     *s);
enum s_type	type_token(char c);
t_token		*token(char *c);
void	lexer(t_input *s);


/////////////////////////////////////////////////////////
//                    B U I L T I N                    //
/////////////////////////////////////////////////////////

void	ft_echo(char **args, t_input *s);
void	ft_env(t_env *env);

void    ft_export(char **args, t_input *s);
void	modify_env(t_input *s);

void    ft_pwd(void);
void	ft_unset(char **args, t_input *s);

/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

/////	parser.c

char    *tlist_to_s(t_list      *list, int l);
void    parser(t_input *s);
int     number_of_groups(t_list *list);


//////////		Q U O T E S		//////////

/////	verif_quotes.c

int     index_quote(char *s, char c);
int     msg_err_quote(void);
int     verif_pair_of_quotes(char *s);

/////	fill_args.c

int     n_space(char *s);
void    clear_quotes(char *s, char ***args);
int     fill_args(t_list *list, t_input *s);


//////////	R E D I R E C T I O N S		////////// 	

/////	cmd_redirections.c

t_cmd   *cmd(int fdi, int fdo, char *args, int id);
void	cmd_redirections(t_list *list, t_input *s);

/////	open_utils.c

void    open_data(t_utils *data, char *r);
void    open_n_close(t_utils *data, int flags, mode_t mode, char *r);
void    open_n_close_hd(t_utils *data);

/////	redirections_utils.c

char    *join_tab(char **tab, int j);
void    modify_redirection(t_utils *data, t_list *plist, t_list *nlist, char *rest_args, char *r);

void    show_cmd_list(t_list *list);
void    clear_cmd_list(t_list *list, t_input *s);


//////////	S E P A R A T O R S 		//////////

//////	cmd_pipes.c

t_cmd   *cmd_index(t_list *list, int index);
void    cmd_pipes(t_list *list, t_input *s);


//////////		U T I L S 		//////////

/////	parser_utils.c

void	clear_space(t_list *list, t_input *s);
t_list	*list_index(t_list *list, int l);

/////	utils.c

int	only_space(char *s);
int	index_separator(t_list *list);
int     nb_token_type(t_list *list, enum s_type type);

/////	verify_separator.c

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







//////////	S I G N A L S . C		//////////

void    ctrl_d(t_input *s);
void    redisplay(int n);
void    sig_int(int n);
void    sig_quit(int n);

/////////////////////////////////////////////////////////
//               	E N V . C                      //
/////////////////////////////////////////////////////////

/////	B U I L T I N S . C 

void	ft_env(t_env *env);
void	ft_printenv(t_input *s);
void	ft_export(char **args, t_input *s);
void	ft_pwd(void);
void	ft_echo(char **args, t_input *s);
void	ft_unset(char **args, t_input *s);

// export_utils.c
void    modify_env(t_input *s);

void    env_to_pipe(t_env *env, int pipe);


/////	E N V . C

void	ft_init(t_input *s, char **env);
void	ft_lstadd_back_env(t_env **s, t_env *env);
int	equal_index(char *env);
t_env   *str_to_env(char *str);
void    show_env(t_env  *env);

void    free_env(t_input *s);
char    **env_to_tab(t_env *env);
void    print_tab_env(t_env *env);
t_env   *ft_lstlast_env(t_input *s);

char    *var_env(char *str, t_input *s);

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

/////	W A I T . C 			/////

void	wait_all(t_input *s, pid_t *f);




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

char    **merge_tab(char **tab, char **tab2);
char    **add_tab(char **tab, char *s, int i);
char    *tab_to_s(char **tab, int f);
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
