# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 13:53:34 by mlavergn          #+#    #+#              #
#    Updated: 2025/04/03 17:02:38 by lecartuy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	minishell
DIR					=	srcs/
DIR_BUILTIN			= 	srcs/builtin/
DIR_LEXER			= 	srcs/lexer/
DIR_PARSER			=	srcs/parser/
DIR_EXECUTION		= 	srcs/execution/
LIBFTDIR			= 	./libft
CC					= 	cc
FLAGS				= 	-Wall -Wextra -Werror

SRCS 		=	${DIR}main.c $(DIR_EXECUTION)check.c $(DIR)utils.c $(DIR_BUILTIN)export.c \
				$(DIR_BUILTIN)unset.c $(DIR_BUILTIN)cd.c $(DIR_BUILTIN)echo.c \
				$(DIR_EXECUTION)pipe.c $(DIR_EXECUTION)redirection.c \
				$(DIR_LEXER)lexer.c $(DIR_BUILTIN)exit.c $(DIR_BUILTIN)pwd.c \
				$(DIR_LEXER)lexer_utils.c $(DIR_PARSER)parser.c  \
				$(DIR_PARSER)expander.c $(DIR_PARSER)expander_utils.c $(DIR_LEXER)quotes_utils.c \
				$(DIR_PARSER)tokenizer.c $(DIR_EXECUTION)command.c $(DIR_EXECUTION)main_exec.c \
				$(DIR_PARSER)tokenizer_utils.c $(DIR_BUILTIN)export_utils.c $(DIR_BUILTIN)cd_utils.c \
				$(DIR_BUILTIN)cd_utils2.c $(DIR)signals.c $(DIR_EXECUTION)utils.c $(DIR_EXECUTION)heredoc.c

OBJS 		= 	$(SRCS:.c=.o)
LIBFT		= 	${LIBFTDIR}/libft.a

HEADERS		=	includes/minishell.h includes/lexer.h includes/parser.h includes/execution.h \
				includes/builtin.h includes/utils.h

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) $(notdir $(LIBFT))

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFTDIR) clean  

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean 

re: fclean all

.PHONY: all clean fclean re

