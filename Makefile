# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 13:53:34 by mlavergn          #+#    #+#              #
#    Updated: 2025/03/11 14:47:27 by mlavergn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	minishell
DIR					=	srcs/
DIR_BUILTIN			= 	srcs/builtin/
DIR_LEXER			= 	srcs/lexer/
DIR_PARSER			=	srcs/parser/
DIR_EXECUTION		=	srcs/execution/
LIBFTDIR			= 	./libft
CC					= 	cc
FLAGS				= 	-Wall -Wextra -Werror -fsanitize=address -g

SRCS 		=	${DIR}main.c $(DIR)check.c $(DIR)utils.c $(DIR_BUILTIN)export.c \
				$(DIR_BUILTIN)unset.c $(DIR_BUILTIN)cd.c $(DIR_BUILTIN)echo.c \
				$(DIR_EXECUTION)pipe.c $(DIR_EXECUTION)redirection.c \
				$(DIR_LEXER)lexer.c $(DIR_BUILTIN)exit.c $(DIR_BUILTIN)pwd.c \
				$(DIR_LEXER)lexer_utils.c $(DIR_PARSER)parser.c $(DIR_PARSER)quotes.c \
				$(DIR_PARSER)expander.c $(DIR_PARSER)expander_utils.c $(DIR_LEXER)quotes_utils.c \
				$(DIR_PARSER)tokenizer.c $(DIR_EXECUTION)command.c $(DIR_EXECUTION)main_exec.c \
				$(DIR_PARSER)tokenizer_utils.c $(DIR_BUILTIN)export_utils.c
OBJS 		= 	$(SRCS:.c=.o)
LIBFT		= 	${LIBFTDIR}/libft.a

all: $(NAME)

%.o: %.c 
	$(CC) $(FLAGS)  -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	@cd $(LIBFTDIR) &&$(MAKE) clean  

fclean: clean
	rm -f $(NAME)
	@cd $(LIBFTDIR) &&$(MAKE) fclean 
	
re: fclean all

.PHONY:	all clean fclean re