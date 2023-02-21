SRCS = main.c parser/get_next_line/get_next_line.c \
		parser/get_next_line/get_next_line_utils.c \
		parser/utils/ft_calloc.c parser/utils/ft_split.c \
		parser/utils/split_utils.c \
		parser/utils/ft_strdup.c parser/utils/ft_substr.c \
		parser/utils/ft_strcmp.c ./parser/linked_list_utils/add_back_lst.c \
		./parser/linked_list_utils/add_front_lst.c \
		./parser/linked_list_utils/create_node.c \
		./parser/linked_list_utils/lst_clear.c\
		./parser/lexer_utils/init_lexer_node.c \
		./parser/lexer_utils/lexer_utils.c \
		./parser/utils/ft_atoi.c \
		./parser/utils/ft_itoa.c \
		./parser/utils/utils.c \
		./parser/parser_utils/parser_utils.c \
		./parser/parser_utils/parser.c \
		./parser/utils/create_mini_env.c \
		./parser/linked_list_utils/env_del_node.c \
		./parser/parser_utils/expand_quotes.c \
		./parser/parser_utils/expand_quotes_utils.c \
		./parser/builtins/builtins_utils.c \
		./parser/builtins/cd.c  \
		./parser/errors_free/parse_error.c \
		./parser/builtins/echo.c  \
		./parser/builtins/env.c  \
		./parser/builtins/exit.c  \
		./parser/builtins/export.c  \
		./parser/builtins/pwd.c  \
		./parser/builtins/unset.c \
		./execution/exec.c
# BONUS_SRCS = actions.c actions_2.c cases.c check_utils.c create_stack.c ft_calloc.c \
# 	ft_split.c ft_strdup.c ft_substr.c push_swap_bonus.c sort_three.c utils.c utils_2.c utils_3.c \
# 	sort_five.c last_sort.c utils_4.c \
# 	get_next_line.c get_next_line_utils.c \
# 	actions_2_bonus.c actions_bonus.c
OBG = $(SRCS:.c=.o)
# BONUS_OBG = $(BONUS_SRCS:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -fsanitize=address -g3
NAME = minishell
# BONUS = checker

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $(CFLAGS) -lreadline $(OBG) -L /Users/ybel-hac/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)
#	make clean
#	./minishell

# bonus: $(BONUS)

# $(BONUS): $(BONUS_OBG)
# 	$(CC) $(CFLAGS) $(BONUS_OBG) -o checker

clean:
	rm -rf $(OBG)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re