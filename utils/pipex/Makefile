# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 18:22:09 by mtellal           #+#    #+#              #
#    Updated: 2022/04/27 14:35:26 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libpipex.a

HEADER = -I includes -I libft/


########################	PIPEX 		#######################

SRC = src/main.c src/error.c src/error_utils.c src/processes.c src/commands.c src/input.c\
	src/utils/free_tab.c src/utils/quote_split.c src/utils/quote_utils.c \

OBJ = $(SRC:.c=.o)


########################	LIBFT		########################

LSRC = ft_memset.c ft_bzero.c ft_memmove.c ft_memcpy.c ft_memccpy.c ft_memchr.c \
      ft_memcmp.c ft_strdup.c  ft_strlcpy.c \
      ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
      ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
      ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
      ft_tolower.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
      ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
      ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
      ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
      get_next_line.c get_next_line_utils.c

LDIR = libft/

LOBJ = $(addprefix $(LDIR), $(LSRC:.c=.o))


#######################		COMMANDS	#########################

all : $(NAME)

%.o:%.c
	$(GCC) $(CFLAGS) $(HEADER) -g -o $@ -c $< 

$(NAME): $(OBJ)
	make -C $(LDIR)
	ar -rc $(NAME) $(OBJ) $(LOBJ)

val: $(NAME)
	valgrind --leak-check=full --tool=memcheck --show-reachable=yes --track-fds=yes --errors-for-leak-kinds=all --show-leak-kinds=all --trace-children=yes ./pipex main.c cat wc output

clean:
	make clean -C $(LDIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LDIR)
	rm -rf $(NAME)

re: fclean all
