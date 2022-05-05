/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:46:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/05 14:50:10 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "libft.h"

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "



//////////		L E X E R		//////////

enum s_type
{
	ALPHANUM,
	REDIRECTION,
	BRACKET,
	PIPE, 
	EXPAND,
	SEPARATOR,
	QUOTES,
	ARITHMETIC,
	OTHERS
};

typedef struct s_token
{
	enum s_type	type;
	char		*str;
	struct s_token	*previous;
	struct s_token	*next;
}		t_token;

//////////////////////////////////////////////////////////

typedef struct s_input
{
	int	argc;
	char	**argv;
	char	**env;

	char	*input;

}		t_input;



int	input(t_input *s, int argc, char **argv, char **env);

int	getInput(t_input *s);

void	init_sinput(t_input *s, int argc, char **argv, char **env);

#endif
