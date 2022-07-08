# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 10:39:17 by mtellal           #+#    #+#              #
#    Updated: 2022/07/07 14:49:51 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell


###############			FILES			###############

SOURCES = main.c minish.c launch.c \

FBUILTIN = echo.c env.c export.c export_utils.c pwd.c unset.c cd.c exit.c \
	unset_utils.c 

FENV = env_init.c env_utils.c env_var.c

FEXECUTER = executer.c executer_utils.c pipes.c err.c signals.c close_utils.c \
	    verif_cmd/verify_commands.c verif_cmd/verify_commands_utils.c \
            status/wait.c  status/status.c 

#####	PARSER	#####

FFILL_ARGS = fill_args.c bracket.c

FPUTILS = utils.c parser_utils.c

FQUOTES = rm_empty_quotes.c clear_tab_quotes.c quote_cleaner.c verif_quotes.c quote_utils.c

FREDIRECTIONS = cmd_redirections.c open_redirections.c cmd_redirections_utils.c heredoc.c utils.c 

FPIPES = cmd_pipes.c verify_separator.c verify_separator_utils.c



#####	UTILS	#####

FUTILS = list_token_utils.c list_cmd_utils.c string_utils.c open_utils.c tab_utils.c tab_utils2.c \
	 free_utils.c debug_utils.c commands_utils.c list_env_utils.c 



#####	SET FOLDERS	#####

BUILTIN = $(addprefix builtin/, $(FBUILTIN))

ENV = $(addprefix env/, $(FENV))

EXECUTER = $(addprefix executer/, $(FEXECUTER) )

EXPANDER = $(addprefix expander/, env_var.c env_var_utils.c )

PARSER = $(addprefix parser/, parser.c lexer.c $(addprefix fill_args/, $(FFILL_ARGS)) $(addprefix utils/, $(FPUTILS)) $(addprefix quotes/, $(FQUOTES)) $(addprefix redirections/, $(FREDIRECTIONS)) $(addprefix pipes/, $(FPIPES)))

UTILS = $(addprefix utils/, $(FUTILS))

SRC = $(addprefix src/, $(SOURCES) $(BUILTIN) $(ENV) $(EXECUTER) $(EXPANDER) $(PARSER) $(UTILS)) 

OBJ = $(SRC:.c=.o)



#####	LIBS/HEADERS	#####

HDIR = includes/

HEADERS = -I $(HDIR) -I ./libft -I $(PDIR)/includes

LIB = -lreadline -L ./libft -lft 



###############                 COMMANDS                   ###############

all: $(NAME)

%.o:%.c
	$(GCC) $(CFLAGS) $(HEADERS) -o $@ -c $<   

$(NAME): $(OBJ)
	make -C ./libft
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
