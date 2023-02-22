# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 21:00:51 by bahbibe           #+#    #+#              #
#    Updated: 2023/02/22 21:01:01 by bahbibe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a
FLAGS = -Wall -Wextra -Werror
SRCS =	get_next_line.c \
		get_next_line_utils.c \
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@:
$(NAME): $(OBJS)
%.o: %.c get_next_line.h
	@cc $(FLAGS) -c $< -o $@
	@ar -rcs $(NAME) $@
clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
.PHONY:all