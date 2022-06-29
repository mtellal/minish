/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/29 15:32:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

	/*
         *      - TESTER:
         *      - 0 env, verifier toutes le cmd une a une + les douilles sur le discord
         *      - 1 signaux avec et sans commandes
         *      - 2 status avec le $?
         *
         *      - 3 les quotes, tout type de test possible, avec sans sep
         *      - 4 les redirections, avec sans quotes, en granc nombre, etc..
         *      - 5 les pipes, beaucoup de pipe, quotes, sep, commande tricky sleep etc
         *      - 6 les cmd, script, absolu relatif, avec erreurs, awk etc
         *
	 * 	- !!!!! builtin =>redirections a set et restore 
	 *	- !!!!! corriger problemes signaux 
	 *	- !!!!! QUOTE HANDLER 
	 *
	 * 	-	export => trier les variables 
	 * 	-	echo -n -n str ( afficher juste str) ou echo -nnnnn str 
	 *
	 * 	- unset s=5 => ne marche pas, param unset alphanum normalament 
         *      - QUOTES => echo "echo \"coucou\"lala"
	 *      - modif les var d'envs => ne pas les modif si pipes genre ls | export d=5 (export fait rien)
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
         *      - verification des fichiers lors dans chaque process
         *      - probleme superposition de *char (stdin et stdout) genre -> ls | cat < dw | pwd
         *      - wdf^C => buffer non reset (wdf toujour la)
         *      - termios et signals
         *	
	 *	CONDITIONS D'ARRET :
	 *	- exit
	 *	- ctrl-D 
	 *
	 *	FREE :
	 *	- input
	 *	- t_list
	 *	- clist
	 *	- cmd_list
	 *	- **pipes
	 *	- *p_env (situationnel) 
	 *	- env
	 *
	 *
	 */

void	init_data(t_input *s, int argc, char **env)
{
	set_last_status(0);
	s->argc = argc;
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
	ft_init(s, env);
	//show_env(s->env);
	//print_tab_env(s->env);
}

void	minishell(t_input *s)
{
	launch_parser(s);
	if (!err_separator(s->clist, s))
	{
		launch_separators(s);
		expander(s->cmd_list, s);
		launch_executer(s);
	}
	free_all(s, 0);
}

int	launch_minishell(t_input *s)
{
	char	*buffer;

	while (1)
	{
		signal(SIGINT, &sig_int);
		set_quit_hd(0);
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
		buffer = NULL;
	}
	rl_clear_history();
	return (0);
}

int	init(t_input *s, int argc, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("error tty stdin invalid\n", 2);
		exit(0);
	}
	init_data(s, argc, env);
	return (0);
}
