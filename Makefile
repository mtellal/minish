# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/05/18 15:17:08 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell


#############		MINISH 		#################
	
SOURCES =	main.c \
	input.c \
	lexer/lexer.c \
	parser/parser.c parser/commands.c parser/commands_utils.c parser/layer2.c \
	parser/utils/parser_utils.c parser/utils/utils.c parser/utils/verify_separator.c \
	parser/utils/list_utils.c parser/utils/order_clist.c \
	executer/verify_commands.c executer/executer.c executer/pipes.c

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
