/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzalugas <bzalugas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:57:46 by bzalugas          #+#    #+#             */
/*   Updated: 2021/10/09 18:59:51 by bzalugas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

size_t	ft_strlen(const char *s);
int		ft_find_char(char c, char *str, size_t start);
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
char	*ft_substr_free(char *s, unsigned int start, size_t len, int free_s);
char	*get_next_line(int fd);

#endif
