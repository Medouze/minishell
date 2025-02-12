# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 13:53:34 by mlavergn          #+#    #+#              #
#    Updated: 2025/02/12 15:00:38 by mlavergn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	minishell
DIR					=	srcs/
DIR_BUILTIN			= 	srcs/builtin/
DIR_LEXER			= 	srcs/lexer/
LIBFTDIR			= 	./libft
CC					= 	cc
FLAGS				= 	-Wall -Wextra -Werror -fsanitize=address -g

SRCS 		=	${DIR}main.c $(DIR)check.c $(DIR)utils.c $(DIR_BUILTIN)export.c \
				$(DIR_BUILTIN)unset.c $(DIR_BUILTIN)cd.c $(DIR_BUILTIN)echo.c $(DIR_LEXER)lexer.c \
				$(DIR_BUILTIN)exit.c $(DIR_BUILTIN)pwd.c
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