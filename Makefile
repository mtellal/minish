# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/06/01 22:08:58 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

#############		MINISH 		#################
	
SOURCES =	main.c \
	minish.c \
	signals.c \
	lexer/lexer.c \
	parser/parser.c\
	parser/redirections/cmd_redirections.c parser/redirections/redirections_utils.c \
	parser/redirections/open_utils.c \
	parser/separators/cmd_pipes.c\
	parser/utils/parser_utils.c parser/utils/utils.c parser/utils/verify_separator.c \
	parser/quotes/verif_quotes.c parser/quotes/fill_args.c  \
	executer/verify_commands.c executer/executer.c executer/pipes.c executer/wait.c \
	utils/tab_utils.c utils/string_utils.c utils/open_utils.c \
	env/env_init.c env/env_utils.c env/env_var.c \
	builtin/env.c builtin/pwd.c builtin/echo.c builtin/export.c builtin/export_utils.c \
	builtin/unset.c

DEBUG = $(addprefix utils/debug/, lexer/debug_lexer.c parser/debug_parser.c parser/commands_utils.c)

SRC = $(addprefix src/, $(SOURCES)) $(DEBUG) 

OBJ = $(SRC:.c=.o)


#############		DIR		#################

LIBDIR = utils/libft


#############		HEADERS		###################	

HDIR = includes/

HEADERS = -I $(HDIR) -I $(LIBDIR) -I $(PDIR)/includes


##############		LIBS		#################

LIB = -lreadline -L $(LIBDIR) -lft 


#############		COMMANDS		##########

all: compiling $(NAME) succeed

succeed:
	@echo "ready\033[0m"

compiling:
	@echo -n "\033[1;32mcompiling"

%.o:%.c
	$(GCC) $(CFLAGS) $(HEADERS) -o $@ -c $<   
	echo -n "."

$(NAME): $(OBJ)
	make -C $(LIBDIR)
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	echo -n "."
clean:
	make clean -C $(LIBDIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -rf $(NAME)

re: fclean all
