/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:42:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/06/01 21:17:36 by mtellal          ###   ########.fr       */
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
	lexer(s);
	parser(s);
	clear_space(s->clist, s);
        if (err_separator(s->clist, s))
                return ;
        show_command_table(s);
        ft_putstr_fd("\n", 2);
        if (index_separator(s->clist) == -1)
                ft_lstadd_back(&s->cmd_list, ft_lstnew(cmd(0, 1, ((t_token*)s->clist->content)->c, 0)));
        else
                redirections(s->clist, s);
        layer2(s->clist, s);
        s->nb_cmd = ft_lstsize(s->cmd_list);
        fill_args(s->cmd_list, s);
        executer(s->cmd_list, s);
        clear_cmd_list(s->cmd_list, s);
	ft_lstclear(&s->clist, &clear_telement);
        
	/*
         *      - verif_cmd =>dans le fork, les cmd precedentes doivents s'exe
         *      - executer les ./wdf et les chemins absolu
         *      - tester les separator dans les quotes '|<fw' | cat etc
         *      - tester les quotes encore
         *      - verifier s'il n'y a aps de douille avec les liens symboliques
         *      - tester avec env -i (sans env) => probleme ls | cat
         *      - env sans arg ni option ( mais env xxx => fonctionne) laisser ou coriger et err si args ou option ?
         *      - faire un tableau de pid et exe tous les fork, + ne pas faire de fork pour les buitlins
         *      - export s+=x aq gerer
         *      - heredoc a supprimer
         *      - shlvl a incrementer lors d'un ./minish
         *      - echo $dws $d | cat -e -> aucun espace
         *      - ft_exit => exit(0) a faire
         *      - segfault '$d $d' s->input vide apres le clear_space
         *      - fonction verifier paire de quote
         *      - exe des commandes avec des dossiers genre ls "./srx"
	 *      - cat ctrl-c / ctl-d => exit status 130 / 0
	 *      - rm le heredoc (unlink)
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
			s->input = var_env(buffer, s);
			s->llist = ft_strlen(s->input);
			if (*buffer)
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
