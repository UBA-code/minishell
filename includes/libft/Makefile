# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 21:01:37 by bahbibe           #+#    #+#              #
#    Updated: 2023/02/23 00:53:56 by bahbibe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS =	ft_atoi.c\
		ft_calloc.c\
		ft_is_space.c\
		ft_itoa.c\
		ft_memset.c\
		ft_split_utils.c\
		ft_split.c\
		ft_strchr.c\
		ft_strcmp.c\
		ft_strdup.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_substr.c\
		ft_tab_free.c\
		ft_putstr.c \

OBJS =$(SRCS:.c=.o)

all: $(NAME)
	@:
$(NAME): $(OBJS)
	@:
%.o: %.c libft.h
	@cc $(FLAGS) -c $< -o $@
	@ar -rcs $(NAME) $@
clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
.PHONY:all