/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/09 10:16:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_data(t_input *s, int argc, char **argv, char **env)
{
	s->argc = argc;
	s->argv = argv;
	s->f_env = env;
	s->input = NULL;
	s->tlist = NULL;
	s->llist = 0;
	s->clist = NULL;
	s->nb_sep = 0;
	s->nb_cmd = 0;
	s->cmd_list = NULL;
	s->nb_pipes = 0;
	s->pipes = NULL;
	s->env = NULL;
	s->p_env = NULL;
	s->lstatus = 0;
	ft_init(s, env);
	//show_env(s->env);
	//print_tab_env(s->env);
}

void	minishell(t_input *s)
{
	if (!ft_strcmp(s->input, "exit"))
		exit(EXIT_SUCCESS);
	lexer(s);
	parser(s);
	clear_space(s->clist);
	if (err_separator(s->clist, s))
	{
		ft_lstclear_lexer(&s->tlist);
		ft_lstclear_token(&s->clist);
		return ;
	}
        if (index_separator(s->clist) == -1)
		       ft_lstaddb_cmd(&s->cmd_list, cmd(0, 1, s->clist->c, 0));
	else if (cmd_redirections(s->clist, s) == -1)
		return ; 
	cmd_pipes(s->clist, s);
	s->nb_cmd = ft_lstsize_cmd(s->cmd_list);
	expander(s->cmd_list, s);
        fill_args(s->cmd_list, s);	
	executer(s->cmd_list, s);
	free_all(s);
	/*
	 * 	- TESTER:
	 * 	- 0 env, verifier toutes le cmd une a une + les douilles sur le discord 
	 * 	- 1 signaux avec et sans commandes
	 * 	- 2 status avec le $?
	 *
	 * 	- 3 les quotes, tout type de test possible, avec sans sep
	 * 	- 4 les redirections, avec sans quotes, en granc nombre, etc..
	 * 	- 5 les pipes, beaucoup de pipe, quotes, sep, commande tricky sleep etc
	 * 	- 6 les cmd, script, absolu relatif, avec erreurs, awk etc  
	 *
         *      - verif_cmd =>dans le fork, les cmd precedentes doivents s'exe
         *      - executer les ./wdf et les chemins absolu
         *      - tester les separator dans les quotes '|<fw' | cat etc
         *      - tester les quotes encore
         *      - verifier s'il n'y a aps de douille avec les liens symboliques
         *      - tester avec env -i (sans env) => probleme ls | cat (err dup2)
         *      - env sans arg ni option ( mais env xxx => fonctionne) laisser ou coriger et err si args ou option ?
         *      - faire un tableau de pid et exe tous les fork, + ne pas faire de fork pour les buitlins
         *      - export s+=x a gerer
         *      - heredoc a supprimer
         *      - shlvl a incrementer lors d'un ./minish
         *      - echo $dws $d | cat -e -> aucun espace
         *      - ft_exit => exit(0) a faire
         *      - segfault '$d $d' s->input vide apres le clear_space
         *      - fonction verifier paire de quote
         *      - exe des commandes avec des dossiers genre ls "./srx"
	 *      - cat ctrl-c / ctl-d => exit status 130 / 0
	 *      - rm le heredoc (unlink)
	 *      - rm pipes ( erro: syntax token '|')
	 *      - !!!!!!!!!!!!!!!!!! FAIRE CD !!!!!!!!!!!!!!!
	 *      - ls | ' ' => err
	 *      - + de test sur les separateurs => || <<<| etc 
         *	- verification des fichiers lors dans chaque process
	 *	- probleme superposition de *char (stdin et stdout) genre -> ls | cat < dw | pwd
	 *	- wdf^C => buffer non reset (wdf toujour la)
	 */
}

int	input(t_input *s)
{
	char	*buffer;

	while (1)
	{
		signal(SIGINT, &sig_int);
		buffer = readline(PROMPT);
		if (!buffer)
			ctrl_d(s);
		add_history(buffer);
		if (verif_pair_of_quotes(buffer) != -1) 
		{
			s->input = ft_strdup(buffer);
			s->llist = ft_strlen(s->input);
			if (s->input && *s->input)
				minishell(s);
		}
		free(buffer);
	}
	return (0);
}

int	launch(t_input *s, int argc, char **argv, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("error tty stdin invalid\n", 2);
		exit(0);
	}
	signal(SIGINT, &sig_int);
	init_data(s, argc, argv, env);
	input(s);
	
	return (0);
}
