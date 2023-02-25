PARSE_PATH= ./src/parser/
EXECUTION_PATH= ./src/execution/

SRCS = main.c $(PARSE_PATH)get_next_line/get_next_line.c \
		$(PARSE_PATH)get_next_line/get_next_line_utils.c \
		$(PARSE_PATH)utils/ft_calloc.c $(PARSE_PATH)utils/ft_split.c \
		$(PARSE_PATH)utils/split_utils.c \
		$(PARSE_PATH)utils/ft_strdup.c $(PARSE_PATH)utils/ft_substr.c \
		$(PARSE_PATH)utils/ft_strcmp.c $(PARSE_PATH)linked_list_utils/add_back_lst.c \
		$(PARSE_PATH)linked_list_utils/add_front_lst.c \
		$(PARSE_PATH)linked_list_utils/create_node.c \
		$(PARSE_PATH)linked_list_utils/lst_clear.c\
		$(PARSE_PATH)lexer_utils/init_lexer_node.c \
		$(PARSE_PATH)lexer_utils/lexer_utils.c \
		$(PARSE_PATH)utils/ft_atoi.c \
		$(PARSE_PATH)utils/ft_itoa.c \
		$(PARSE_PATH)utils/utils.c \
		$(PARSE_PATH)parser_utils/parser_utils.c \
		$(PARSE_PATH)parser_utils/parser.c \
		$(PARSE_PATH)utils/create_mini_env.c \
		$(PARSE_PATH)linked_list_utils/env_del_node.c \
		$(PARSE_PATH)parser_utils/expand_quotes.c \
		$(PARSE_PATH)parser_utils/expand_quotes_utils.c \
		$(PARSE_PATH)builtins/builtins_utils.c \
		$(PARSE_PATH)builtins/cd.c  \
		$(PARSE_PATH)errors_free/parse_error.c \
		$(PARSE_PATH)builtins/echo.c  \
		$(PARSE_PATH)builtins/env.c  \
		$(PARSE_PATH)builtins/exit.c  \
		$(PARSE_PATH)builtins/export.c  \
		$(PARSE_PATH)builtins/pwd.c  \
		$(PARSE_PATH)builtins/unset.c \
#		$(EXECUTION_PATH)executor.c
#		$(EXECUTION_PATH)exec.c

OBG = $(SRCS:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -fsanitize=address -g3
NAME = minishell

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $(CFLAGS) -lreadline $(OBG) -L ~/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)

clean:
	rm -rf $(OBG)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re