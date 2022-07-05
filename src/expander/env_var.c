/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:11:27 by mtellal           #+#    #+#             */
/*   Updated: 2022/07/04 21:38:36 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	v_value(char **f, char *s, t_input *ss)
{
	int	i;
	char	*sub;
	char	*final;

	i = 0;
	final = NULL;
	if (s[i] == '$')
		i++;
	if (s[i] == '\0')
		return (i);
	while (s && s[i] && (s[i] =='_' || ft_isalnum(s[i])))
		i++;
	sub = ft_substr(s, 0, i);
	final = value_attr(sub + 1, ss);
	if (final)
		ss->value = 1;
	else
		ss->value = 0;
	if (!final && i == 1)
	{
		*f = add_char(*f, sub[i]);
		free(sub);
	}
	else if (final)
		*f = ft_strjoin_free(*f, final, 1, 1);
	return (i);
}

char    *var_env(char *s, t_input *ss)
{
        int             i;
        int             quote;
        char    *final;

        i = 0;
        final = NULL;
        quote = 0;
        while (s && s[i])
        {
		if (!quote && ft_belong("'\"", s[i]))
			quote = s[i];
		else if (quote && ft_belong("'\"", s[i]))
			quote = 0;
		if (s[i] == '$')
			i += v_value(&final, s + i, ss);
		else
		{
			final = add_char (final, s[i]);	
			i++;
		}
	}
	if (final)
	{
		free(s);
		return (final);
	}
	else
        	return (s);
}
