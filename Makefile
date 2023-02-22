# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 20:45:41 by bahbibe           #+#    #+#              #
#    Updated: 2023/02/23 00:54:58 by bahbibe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Off		=\033[0m
Black	=\033[0;30m
Red		=\033[0;31m
Green	=\033[0;32m
Yellow	=\033[0;33m
Blue	=\033[0;34m
Purple	=\033[0;35m
Cyan	=\033[0;36m
White	=\033[0;37m

CC		=	cc
NAME	=	minishell
FLAGS	=	-Wall -Wextra -Werror 

SRCS	=	minishell.c \
			src/parser/builtins/builtins_utils.c \
			src/parser/builtins/cd.c \
			src/parser/builtins/echo.c \
			src/parser/builtins/env.c \
			src/parser/builtins/exit.c \
			src/parser/builtins/export.c \
			src/parser/builtins/pwd.c \
			src/parser/builtins/unset.c \
			src/parser/errors_free/parse_error.c \
			src/parser/lexer_utils/init_lexer_node.c \
			src/parser/lexer_utils/lexer_utils.c \
			src/parser/linked_list_utils/add_back_lst.c \
			src/parser/linked_list_utils/add_front_lst.c \
			src/parser/linked_list_utils/create_node.c \
			src/parser/linked_list_utils/env_del_node.c \
			src/parser/linked_list_utils/lst_clear.c \
			src/parser/linked_list_utils/lst_size.c \
			src/parser/parser_utils/expand_quotes_utils.c \
			src/parser/parser_utils/expand_quotes.c \
			src/parser/parser_utils/parser_utils.c \
			src/parser/parser_utils/parser.c \
			src/parser/utils/create_mini_env.c \
			src/parser/utils/utils.c \

LIBS		=	libft gnl

INCLUDES	=	$(LIBS:%=includes/$*/%.a)

all: $(LIBS) $(NAME)
	@:
$(NAME): $(SRCS)
	@$(CC) -I includes  $(FLAGS) $(SRCS) $(INCLUDES) -lreadline -L ~/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)
	@echo "$(Green)MINISHELL READY ✅$(Off)"
libs: $(LIBS)
$(LIBS):
	@make -C includes/$@
	@cp includes/$@/$@.a includes
clean:
	@make -C includes/libft clean
	@make -C includes/gnl clean
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(B_NAME)
	@rm -rf $(INCLUDES)
re: fclean all
.PHONY: all