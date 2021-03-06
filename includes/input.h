/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/10 10:14:46 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell> "
# define PATH_MAX 4096

enum e_type
{
	ALPHANUM,
	SEPARATOR,
};

typedef struct s_token
{
	enum e_type		type;
	char			*c;
	struct s_token	*next;
}		t_token;

typedef struct s_cmd
{
	int				id;
	int				fdi;
	int				fdo;
	char			*args;
	char			*cmd;
	char			**cmd_args;
	char			*err_redir;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_env
{
	int				len;
	int				equal;
	char			*var;
	char			*content;
	struct s_env	*next;
}		t_env;

typedef struct s_utils
{
	int		fdi;
	int		fdo;
	int		i_list;
	int		i_cmd;
	int		file;
	char	**tab;
	char	*err_redir;
	t_token	*list;
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
	int				argc;
	int				nb_sep;
	int				nb_cmd;
	int				nb_pipes;
	int				**pipes;
	int				hd;
	char			*input;
	struct s_token	*tlist;
	struct s_token	*clist;
	struct s_cmd	*cmd;
	struct s_env	*env;	
}		t_input;

/////   minish.c
int		launch_minishell(t_input *s);
int		init(t_input *s, int argc, char **env);
void	init_data(t_input *s, int argc, char **env);
void	minishell(t_input *s);

/////   launch.c
void	launch_parser(t_input *s);
void	launch_separators(t_input *s);
void	launch_executer(t_input *s);

/////////////////////////////////////////////////////////
//                    B U I L T I N                    //
/////////////////////////////////////////////////////////

void	ft_echo(char **args, t_input *s);
void	ft_env(t_env *env, t_input *s);
void	ft_exit(t_cmd *cmd, t_input *s);
void	ft_cd(char **args, t_input *s);

/////	export_utils.c
void	ft_export(char **args, t_input *s);
void	env_to_pipe(t_env *env, int *pipe);
void	update_env(t_input *s);

int		ft_str_valid_var(char *str);
void	ft_pwd(int i, t_input *s);
void	ft_unset(char **args, t_input *s);

/////	unset_utils.c
int		lst_size_env(t_env *env);
int		msg_err_unset(char *tab);
void	free_tenv(t_env *e);

/////////////////////////////////////////////////////////
//                       E N V	                       //
/////////////////////////////////////////////////////////

/////	env_init.c
int		equal_index(char *env);
void	ft_init(t_input *s, char **envp);
void	ft_lstadd_back_env(t_env **lst, t_env *n);
t_env	*str_to_env(char *str);

/////	env_utils.c
t_env	*var_exists(char *var, t_env *lenv);
char	*get_var_value(char *var, t_input *s);
void	set_var_value(char *var, char *value, t_input *s);
void	free_env(t_env **env);
char	**env_to_tab(t_env *env);
t_env	*ft_lstlast_env(t_input *s);

/////////////////////////////////////////////////////////
//                   E X P A N D E R                   //
/////////////////////////////////////////////////////////

/////   env_var.c
int		end_index_var(char *s);
char	*value_attr(char *attr, t_input *s);
char	*var_value(char *s, t_input *ss);
char	*var_env(char *s, t_input *ss);

/////   env_var_utils.c
int		end_index_var(char *s);
char	*value_attr(char *attr, t_input *s);
char	*var_value(char *s, t_input *ss);

/////////////////////////////////////////////////////////
//               E X E C U T E R  . C                  //
/////////////////////////////////////////////////////////

/////	executer.c
void	set_fds(t_cmd *cmd);
void	close_fds_execute(t_input *s);
void	execute(t_cmd *cmd, char **args, t_input *s);
void	executer(t_cmd *list, t_input *s);

/////	executer_utils.c
int		*pipe_env(t_cmd *cmd, int nb_cmd);
int		is_builtin(char *args);
void	update_shlvl(t_input *s);
void	need_update_env(t_cmd *cmd, t_input *s);
void	builtin(t_cmd *cmd, t_input *s);

/////	pipes.c
int		**create_pipes(int nb_pipes);
void	set_pipes(t_cmd *list, t_input *s);

/////	verify_commands.c
int		valid_cmd(char *path, char *cmdi);
char	**tab_path(char **env);
char	**add_tab_first(char *s, char **tab);
char	*is_valid_cmd(t_cmd *cmd, char **env, t_input *s);

/////	verify_commands_utils.c
char	*wrap_bash(char *s, char **env, t_input *ss);
void	err_msg_invalid_cmd(char *cmd, char **env, t_input *s);
void	err_msg_redir(t_cmd *c, t_input *s, int builtin);
void	err_execve(char **env, char *cmd, t_input *s);

/////	wait.c
int		get_last_pid(void);
void	set_last_pid(int pid);
void	wait_all(t_input *s, pid_t *f);

/////	close_utils.c
void	set_fds(t_cmd *cmd);
void	close_fds(t_input *s);
void	close_pipes(int **pipes, int nb_pipes);
void	restore_fds(t_coor fds);

/////	utils_status.c
int		get_last_status(void);
void	set_last_status(int status);
void	return_status(int status, t_input *s);

/////   signals.c
void	exec_sig_int(int n);
void	sig_int(int n);
void	exec_sig_quit(int n);
void	init_exec_signals(void);
void	sig_int_hd(int n);

/////////////////////////////////////////////////////////
//                      P A R S E R                    //
/////////////////////////////////////////////////////////

/////	lexer.c
int		type_token(char c);
void	clear_telement(void *s);
void	lexer(t_input *s);

/////	parser.c
int		number_of_groups(t_token *list);
void	parser(t_input *s);

//////////           F I L L _ A R G S          //////////

/////   fill_args.c
void	fill_args(t_cmd *cmd, t_input *s);

/////	bracket.c
int		bracket_inside(char *s);
char	**join_brackets(char **args);

//////////		Q U O T E S		//////////

/////	rm_empty_quotes
char	*remove_empty_quotes(char *s);

/////	clear_tab_quotes.c
int		nb_quotes(char *s);
char	**clear_tab(char **tab);

/////	quote_cleaner.c
void	quote_cleaner(t_input *s);

/////	verif_quotes.c
int		verif_pair_of_quotes(char *s);

/////	quote_utils.c
int		quote_inside(char *s);
char	**quote_split(char *s);
void	add_word_space(char **s, char **final, int i);

//////////	R E D I R E C T I O N S		////////// 	

/////	cmd_redirections.c
void	progress_list(t_utils *data, t_input *s, char *rest_args);
void	cmd_redirections(t_token *list, t_input *s);

/////	open_utils.c
int		open_data(t_utils *data, char *r);
int		open_n_close(t_utils *data, int flags, mode_t mode, char *r);

/////	heredoc.c
int		get_quit_hd(void);
int		open_n_close_hd(t_utils *data);
void	set_quit_hd(int n);

/////	redirections_utils.c
void	init_cmd_redir(t_utils *data, t_input *s, char *r);
void	add_cmd(t_utils *data, t_input *s, char **rest_args, char *r);
void	modify_redirection(t_utils *data, char *rest_args, char *r);

/////	utils.c
void	free_utils_data(t_utils *data);

//////////		P I P E S 		//////////

//////	cmd_pipes.c
t_cmd	*cmd_index(t_cmd *list, int index);
void	cmd_pipes(t_token *list, t_input *s);

/////	verify_separator.c
int		err_separator(t_token *list, t_input *s);

/////	verify_separator_utils.c
int		msg_err_separator(char *s, int err_sep);
int		err_redi(t_token *list, t_token *nlist);

//////////		U T I L S 		//////////

/////	parser_utils.c
t_cmd	*cmd_index(t_cmd *list, int index);
void	clear_space(t_token *list, t_input *s);
t_token	*list_index_token(t_token *list, int l);

/////	utils.c
int		only_space(char *s);
int		index_separator(t_token *list);
int		nb_token_type(t_token *list, enum e_type type);
t_cmd	*cmd(int fdi, int fdo, char *args, int id);

/////	verify_separator.c
int		same_char(char *s, char c, int l);
int		valid_separator(char *s, int *err_sep);
int		msg_err_separator(char *s, int err_sep);
int		err_separator(t_token *list, t_input *s);

/////////////////////////////////////////////////////////
//                      U T I L S                      //
/////////////////////////////////////////////////////////

/////   tab_utils.c
int		ft_strlen_tab(char **tab);
char	**merge_tab(char **tab, char **tab2);
char	**add_tab(char **tab, char *s, int ftab, int fs);
char	*tab_to_s(char **tab, int f);
void	free_tab(char **tab);

/////	tab_utils2.c
void	print_tab(char **tab);
char	*join_tab(char **tab, int j, int ftab);

/////   string_utils.c
int		ft_belong(char *s, char c);
char	*add_char(char *s, char c);

/////   open_utils.c
int		ft_open(int *fd, char *file, int flags, mode_t mode);

/////	list_token_utils.c
int		ft_lstsize_token(t_token *llist);
void	free_token(t_token **token);
void	ft_lstaddb_token(t_token **lst, t_token *n);
t_token	*list_index_token(t_token *list, int l);

/////	list_cmd_utils.c
int		ft_lstsize_cmd(t_cmd *list);
void	free_cmd(t_cmd *cmd);
void	ft_lstaddb_cmd(t_cmd **lst, t_cmd *n);
void	ft_lstclear_cmd(t_cmd **list);
t_cmd	*list_index_cmd(t_cmd *list, int l);

/////	free_utils.c
void	ctrl_d(t_input *s);
void	free_all(t_input *s, int env);

/////	env_utils.c
void	show_env(t_env *env);
void	print_tab_env(t_env *env);

////	list_env_utils.c
int		ft_lstenv_size(t_env *env);

/////	debug_utils.c
void	show_lexer(t_input *s);
void	show_parser(t_input *s);

/////	commands_utils.c
void	clear_cmd_list(t_cmd **cmd);
void	show_cmd_list(t_cmd *lcmd);

#endif
