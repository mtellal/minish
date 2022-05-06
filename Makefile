# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/05/06 15:03:49 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell


#############		MINISH 		#################
	
SOURCES =	main.c \
	input/input.c \
	input/lexer/lexer.c \
	input/parser/parser.c input/parser/parser_utils.c

DEBUG = $(addprefix utils/debug/, lexer/debug_lexer.c parser/debug_parser.c)

SRC = $(addprefix src/, $(SOURCES)) $(DEBUG) 

OBJ = $(SRC:.c=.o)


#############		DIR		#################

PDIR = utils/pipex

LIBDIR = $(PDIR)/libft


#############		HEADERS		###################	

HDIR = includes/

HEADERS = -I $(HDIR) -I $(LIBDIR) -I $(PDIR)/includes


##############		LIBS		#################

LIB = -lreadline -L $(LIBDIR) -lft -L $(PDIR) -lpipex


#############		COMMANDS		##########

all: $(NAME)

%.o:%.c
	$(GCC) $(CFLAGS) $(HEADERS) -o $@ -c $<   

$(NAME): $(OBJ)
	make -C $(PDIR)
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

clean:
	make clean -C $(PDIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(PDIR)
	rm -rf $(NAME)

re: fclean all
