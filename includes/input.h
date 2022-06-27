/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/27 11:25:57 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "
#define PATH_MAX 4096

enum s_type
{
	ALPHANUM,
	SEPARATOR,
};

typedef struct s_token
{
	enum s_type	type;
	char		*c;
	struct s_token	*next;
}		t_token;

typedef struct s_cmd
{
	int		id;
	char		*args;
	int		fdi;
	int		fdo;
	char		**cmd_args;
	char		*cmd;
	char		*err_redir;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_env
{
	char	*var;
	char	*content;
	int		len;
	struct s_env	*next;

}		t_env;

typedef struct s_utils
{
	int	fdi;
	int	fdo;
	int	i_list;
	int	i_cmd;
	int	file;
	char	**tab;
	char	*err_redir;
	t_token	*token;
	t_token	*ptoken;
	t_token	*ntoken;
	t_cmd	*cmd;
	t_cmd	*pcmd;
	t_cmd	*ncmd;
}		t_utils;

typedef struct s_quote
{
	int	f_quote;
	int	l_quote;
}		t_quote;

typedef struct s_coor
{
	int	i;
	int	j;
}		t_coor;

typedef struct s_input
{
	int		argc;
	int		llist;
	int		nb_sep;
	int		nb_cmd;
	int		nb_pipes;
	int		**pipes;
	int		hd;
	int		*p_env;
	int		lstatus;
	char	*input;
	struct s_token	*tlist;
	struct s_token	*clist;
	struct s_cmd	*cmd_list;
	struct s_env	*env;

}		t_input;


/////   minish.c
void    init_data(t_input *s, int argc, char **env);
void    minishell(t_input *s);
int     launch_minishell(t_input *s);
int     init(t_input *s, int argc, char **env);

/////   launch.c
void    launch_parser(t_input *s);
void    launch_separators(t_input *s);
void    launch_executer(t_input *s);


/////////////////////////////////////////////////////////
//                    B U I L T I N                    //
/////////////////////////////////////////////////////////

void	ft_echo(char **args, t_input *s);
void	ft_env(t_env *env, t_input *s);
void	ft_exit(t_cmd *cmd, t_input *s);
void	ft_cd(char **args, t_input *s);

/////	export_utils.c
void    ft_export(char **args, t_input *s);
void	env_to_pipe(t_env *env, int *pipe);
void	update_env(t_input *s);

int     ft_str_valid(char *str);
void    ft_pwd(int i, t_input *s);
void	ft_unset(char **args, t_input *s);


/////////////////////////////////////////////////////////
//                       E N V	                       //
/////////////////////////////////////////////////////////

/////	env_init.c
void   ft_init(t_input *s, char **envp);
void	ft_lstadd_back_env(t_env **lst, t_env *n);
int	equal_index(char *env);
t_env	*str_to_env(char *str);

/////	env_utils.c
t_env	*var_exists(char *var, t_env *lenv);
char	*get_var_value(char *var, t_input *s);
void	set_var_value(char *var, char *value, t_input *s);
void	free_env(t_input *s);
char	**env_to_tab(t_env *env);
t_env	*ft_lstlast_env(t_input *s);


/////////////////////////////////////////////////////////
//                   E X P A N D E R                   //
/////////////////////////////////////////////////////////

/////	expander.c
void	expander(t_cmd *lcmd, t_input *s);

/////   env_var.c
int     end_index_var(char *s);
char    *value_attr(char *attr, t_input *s);
char    *var_value(char *s, t_input *ss);
char    *var_env(char *s, t_input *ss);

/////   env_var_utils.c
int     end_index_var(char *s);
char    *value_attr(char *attr, t_input *s);
char    *var_value(char *s, t_input *ss);


/////////////////////////////////////////////////////////
//               E X E C U T E R  . C                  //
/////////////////////////////////////////////////////////

/////	executer.c
void	set_fds(t_cmd *cmd);
void	close_fds_execute(t_input *s);
void	execute(t_cmd *cmd, char **args, t_input *s);
void    executer(t_cmd *list, t_input *s);

/////	executer_utils.c
void	need_update_env(t_cmd *cmd, t_input *s);
int	*pipe_env(t_cmd *cmd, int nb_cmd);
void	builtin(t_cmd *cmd, t_input *s);
int	is_builtin(char *args);

/////	pipes.c
int	**create_pipes(int nb_pipes);
void    set_pipes(t_cmd *list, t_input *s);

/////	verify_commands.c
char    **tab_path(char **env);
int     valid_cmd(char *path, char *cmdi);
char	**add_tab_first(char *s, char **tab);
char	*wrap_bash(char *s);
char    *is_valid_cmd(char *cmd, char **env);

/////	verify_commands_utils.c
char	*wrap_bash(char *s);
void	err_msg_invalid_cmd(char *cmd);

/////	wait.c
void    wait_all(t_input *s, pid_t *f);

/////	close_utils.c
void    set_fds(t_cmd *cmd);
void    close_fds(t_input *s);
void    close_pipes(int **pipes);

/////	err.c
void    err_msg_cmd(char *cmd);
void    err_cmd(t_cmd *cmd, t_input *s, int msg);


/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

/////	lexer.c
void    clear_telement(void     *s);
enum s_type     type_token(char c);
t_token         *token(char *c);
void    lexer(t_input *s);

/////	parser.c
char    *tlist_to_s(t_token *list, int l);
void    parser(t_input *s);
int     number_of_groups(t_token *list);

//////////		Q U O T E S		//////////

/////	verif_quotes.c
int     index_quote(char *s, char c);
int     msg_err_quote(void);
int     verif_pair_of_quotes(char *s);

/////	fill_args.c
int     n_space(char *s);
void    clear_quotes(char *s, char ***args);
int     fill_args(t_cmd *list, t_input *s);

/////	tab_quotes.c
int     n_space(char *s);
char    **return_tab(char **tab, char *ns, char *s, int i);
void    progress_next_word(char ***tab, char *s, char **ns, int *i);
void    nspace_in_quotes(int lfquote, char *s, char **ns, int *i);
void    init_tab_quotes(t_quote *q, int *i, char ***tab, char **ns);

/////	clear_word.c
void	set_first_char(int f_quote, char **ns, char *s, int i);
void	set_i_fquote(int *i, int *fquote, int vi, int vfquote);
char	*no_more_quotes(char *ms, char *s, int i, char _quote);
void    init_clear_word(int *i, char *quote, char **ns);

//////////	R E D I R E C T I O N S		////////// 	

/////	cmd_redirections.c
t_cmd   *cmd(int fdi, int fdo, char *args, int id);
void    progress_list(t_utils *data, t_input *s, char *rest_args);
void	cmd_redirections(t_token *list, t_input *s);

/////	open_utils.c
int	open_data(t_utils *data, char *r);
int	open_n_close(t_utils *data, int flags, mode_t mode, char *r);
int	open_n_close_hd(t_utils *data);

/////	redirections_utils.c
void    err_msg_redirection(char *err);
void     init_cmd_redir(t_utils *data, t_input *s, char *r);
void    add_cmd(t_utils *data, t_input *s, char **rest_args, char *r);
char    *join_tab(char **tab, int j, int ftab);
void    modify_redirection(t_utils *data, char *rest_args, char *r);

void    show_cmd_list(t_cmd *list);
void    clear_cmd_list(t_cmd **list);


//////////	S E P A R A T O R S 		//////////

//////	cmd_pipes.c
t_cmd   *cmd_index(t_cmd *list, int index);
void    cmd_pipes(t_token *list, t_input *s);


//////////		U T I L S 		//////////

/////	parser_utils.c
t_cmd	*cmd_index(t_cmd *list, int index);
void	clear_space(t_token *list);
t_token	*list_index_token(t_token *list, int l);

/////	utils.c
int	only_space(char *s);
int	index_separator(t_token *list);
int     nb_token_type(t_token *list, enum s_type type);

/////	verify_separator.c
int     same_char(char *s, char c, int l);
int     valid_separator(char    *s, int *err_sep);
int     msg_err_separator(char *s, int err_sep);
int     err_separator(t_token *list, t_input *s);



//////////	S I G N A L S . C		//////////

/////	signals.c
void    ctrl_d(t_input *s);
void    redisplay(int n);
void    sig_int(int n);
void    sig_quit(int n);



/////////////////////////////////////////////////////////
//                      U T I L S                      //
/////////////////////////////////////////////////////////

/////   tab_utils.c
char    **merge_tab(char **tab, char **tab2);
char    **add_tab(char **tab, char *s, int fs, int ftab);
char    *tab_to_s(char **tab, int f);
int     ft_strlen_tab(char **tab);
void    free_tab(char **tab);

/////	tab_utils2.c
void	print_tab(char **tab);

/////   string_utils.c
int     ft_belong(char *s, char c);

/////   open_utils.c
int     ft_open(int *fd, char *file, int flags, mode_t mode);

/////	list_token_utils.c
void    free_token(t_token **token);
void    ft_lstaddb_token(t_token **lst, t_token *n);
void	ft_lstclear_token(t_token **token);
t_token *list_index_token(t_token *list, int l);
void    ft_lstclear_lexer(t_token **list);

/////	list_cmd_utils.c
int     ft_lstsize_cmd(t_cmd *list);
void    free_cmd(t_cmd *cmd);
void    ft_lstaddb_cmd(t_cmd **lst, t_cmd *n);
void    ft_lstclear_cmd(t_cmd **list);
t_cmd *list_index_cmd(t_cmd *list, int l);

/////	free_utils.c
void	free_all(t_input *s);

/////	env_utils.c
void	show_env(t_env *env);
void	print_tab_env(t_env *env);


/////////////////////////////////////////////////////////
//                      D E B U G                      //
/////////////////////////////////////////////////////////

/////	deubg_lexer.c
void	show_token_list(t_input *s);

////	debug_parser.c
void	show_command_table(t_input *s);

#endif
