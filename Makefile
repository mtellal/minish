# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/06/04 14:08:53 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

#############		MINISH 		#################

BUILTIN = $(addprefix builtin/, echo.c env.c export.c export_utils.c pwd.c unset.c)

ENV = $(addprefix env/, env_init.c env_utils.c env_var.c env_var_utils.c)

EXECUTER = $(addprefix executer/, executer.c executer_utils.c pipes.c verify_commands.c verify_commands_utils.c wait.c)


#####	PARSER

PUTILS = $(addprefix utils/, utils.c parser_utils.c verify_separator.c)

QUOTES = $(addprefix quotes/, clear_word.c fill_args.c tab_quotes.c verif_quotes.c)

REDIRECTIONS = $(addprefix redirections/, cmd_redirections.c  open_redirections.c redirections_utils.c)

SEPARATORS = $(addprefix separators/, cmd_pipes.c)

PARSER = $(addprefix parser/, parser.c $(PUTILS) $(QUOTES) $(REDIRECTIONS) $(SEPARATORS))

#####	UTILS

DEBUG = $(addprefix debug/, debug_lexer.c debug_parser.c commands_utils.c)

UTILS = $(addprefix utils/, list_token_utils.c list_cmd_utils.c open_utils.c string_utils.c tab_utils.c $(DEBUG))

SOURCES = main.c minish.c lexer/lexer.c signals.c \

SRC = $(addprefix src/, $(SOURCES) $(BUILTIN) $(ENV) $(EXECUTER) $(PARSER) $(UTILS)) 

OBJ = $(SRC:.c=.o)


#############		DIR		#################

LIBDIR = ./libft


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
