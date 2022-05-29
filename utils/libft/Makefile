# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/06 10:01:48 by mtellal           #+#    #+#              #
#    Updated: 2022/05/29 22:01:38 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memmove.c ft_memcpy.c ft_memccpy.c ft_memchr.c \
      ft_memcmp.c ft_strdup.c  ft_strlcpy.c\
      ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
      ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
      ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
      ft_tolower.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
      ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
      ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
      ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
      get_next_line.c get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -g -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
