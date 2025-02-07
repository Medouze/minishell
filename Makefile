# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 13:53:34 by mlavergn          #+#    #+#              #
#    Updated: 2025/02/07 17:37:15 by mlavergn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	minishell
DIR			= 	srcs/
LIBFTDIR	= 	./libft
CC			= 	cc
FLAGS		= 	-Wall -Wextra -Werror -fsanitize=address -g

SRCS 		=	${DIR}main.c $(DIR)check.c $(DIR)builtin.c $(DIR)utils.c $(DIR)export.c \
				$(DIR)unset.c $(DIR)cd.c $(DIR)lexer.c
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