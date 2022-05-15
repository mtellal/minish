/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:18:51 by mtellal           #+#    #+#             */
/*   Updated: 2022/05/13 17:17:51 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
 *	renvoie le nb de char* dans un tab
 */

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*
 *	free chaque char* dans un tab, ainsi que tab
 */

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}


/*
 *	verifie s'il y a un separateur dans une liste
 *	et renvoie son index
 *	utile pour isoler les cmd
 */

int	index_separator(t_list *list)
{
	int	i;
	t_token	*token;

	i = 0;
	while (list)
	{
		token = list->content;
		if (token->type == SEPARATOR && !only_space(token->c))
			return (i);
		list = list->next;
		i++;
	}
	return (-1);
}

/*
 *	renvoie le nombre de token du type 'type' dans la liste
 */

int     nb_token_type(t_list *list, enum s_type type)
{
        int     i;
        t_token *token;

        i = 0;
        while (list)
        {
                token = list->content;
                if (token->type == type)
                        i++;
                list = list->next;
        }
        return (i);
}
