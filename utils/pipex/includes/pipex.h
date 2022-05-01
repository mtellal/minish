/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:38:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/01 17:17:59 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"

typedef struct s_err {
	int	cmd;
	int	args;
}		t_err;

typedef struct s_data {
	int		argc;
	char	**argv;
	char	**env;
}		t_data;

typedef struct s_pip {
	int		hd;
	int		fdi;
	int		fdo;
	int		**pipe;
	char	***arg;
	char	**cmd;
	t_data	data;
	t_err	err;
}		t_pip;

/////		MAIN			/////

//int		pipex(int argc, char **argv, char **env);

/////		PROCESSES		/////

void	close_all_pipes(t_pip *s);
void	processes(t_pip *s);

/////		COMMAND			/////

void	fill_commands(t_pip *s, int nbc);

/////		ERROR 			/////

void	close_files(t_pip *s);
void	err(char *err, int eno);
void	ft_dup2(int n, int old);
void	ft_pipe(int i, t_pip *s);
void	free_s(t_pip *s, int pipe, int args, int cmd);

/////		ERROR_UTILS		/////

int		ft_dup(int fd);
int		ft_open(int *fd, char *file, int flags, mode_t mode);
void	free_args(t_pip *s);
void	free_cmd(t_pip *s);

/////		INPUT			/////

void	get_input(t_pip *s);

void	free_tab(char **p);
void	fill_args(t_pip *s, char **argv, int nbc);
int		quote_block(char *s);
char	*rm_quote(char*s);
char	**p_q(char **tab);
char	**fusion_tab(char **t, char **t2);
void	ft_malloc(t_pip *s, char **t, size_t m);

#endif 
