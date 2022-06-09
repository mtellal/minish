# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/06/09 11:39:13 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell


#####	FILES	#####

SOURCES = main.c minish.c lexer/lexer.c signals.c \

FBUILTIN = echo.c env.c export.c export_utils.c pwd.c unset.c exit.c

FENV = env_init.c env_utils.c

FEXECUTER = executer.c executer_utils.c pipes.c verify_commands.c verify_commands_utils.c \
            wait.c close_utils.c err.c

#####	PARSER	#####

FPUTILS = utils.c parser_utils.c verify_separator.c

FQUOTES = clear_word.c fill_args.c tab_quotes.c verif_quotes.c

FREDIRECTIONS = cmd_redirections.c open_redirections.c redirections_utils.c

FSEPARATORS = cmd_pipes.c



#####	UTILS	#####

FUTILS = list_token_utils.c list_cmd_utils.c string_utils.c open_utils.c tab_utils.c free_utils.c \
	 debug_lexer.c debug_parser.c commands_utils.c



#####	SET FOLDERS	#####

BUILTIN = $(addprefix builtin/, $(FBUILTIN))

ENV = $(addprefix env/, $(FENV))

EXECUTER = $(addprefix executer/, $(FEXECUTER) )

EXPANDER = $(addprefix expander/, env_var.c env_var_utils.c expander.c)


PARSER = $(addprefix parser/, parser.c $(addprefix utils/, $(FPUTILS)) $(addprefix quotes/, $(FQUOTES)) $(addprefix redirections/, $(FREDIRECTIONS)) $(addprefix separators/, $(FSEPARATORS)))

UTILS = $(addprefix utils/, $(FUTILS))

SRC = $(addprefix src/, $(SOURCES) $(BUILTIN) $(ENV) $(EXECUTER) $(EXPANDER) $(PARSER) $(UTILS)) 

OBJ = $(SRC:.c=.o)



#####	LIBS/HEADERS	#####

HDIR = includes/

HEADERS = -I $(HDIR) -I ./libft -I $(PDIR)/includes

LIB = -lreadline -L ./libft -lft 



#####	COMMANDS	#####

all: compiling $(NAME) succeed

succeed:
	@echo "ready\033[0m"

compiling:
	@echo -n "\033[1;32mcompiling"

%.o:%.c
	$(GCC) $(CFLAGS) $(HEADERS) -o $@ -c $<   
	echo -n "."

$(NAME): $(OBJ)
	make -C ./libft
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	echo -n "."
clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
