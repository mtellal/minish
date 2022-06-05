/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzalugas <bzalugas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:57:41 by bzalugas          #+#    #+#             */
/*   Updated: 2021/10/13 15:13:29 by bzalugas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_the_line(char **text, int end_line)
{
	char	*line;

	if (!*text || !**text)
	{
		if (*text)
		{
			free(*text);
			*text = NULL;
		}
		return (NULL);
	}
	if (end_line == -1)
		end_line = ft_strlen(*text);
	line = ft_substr_free(*text, 0, end_line + 1, 0);
	*text = ft_substr_free(*text, end_line + 1, ft_strlen(*text), 1);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*text = NULL;
	int			end_line;
	int			result;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	end_line = ft_find_char('\n', text, 0);
	if (end_line == -1)
		result = read(fd, buff, BUFFER_SIZE);
	while (end_line == -1 && result > 0)
	{
		buff[result] = '\0';
		text = ft_strjoin_free(text, buff, 1, 0);
		end_line = ft_find_char('\n', text, 0);
		if (end_line == -1)
			result = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (get_the_line(&text, end_line));
}
