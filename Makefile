SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		utils/ft_calloc.c utils/ft_split.c utils/ft_strdup.c utils/ft_substr.c
# BONUS_SRCS = actions.c actions_2.c cases.c check_utils.c create_stack.c ft_calloc.c \
# 	ft_split.c ft_strdup.c ft_substr.c push_swap_bonus.c sort_three.c utils.c utils_2.c utils_3.c \
# 	sort_five.c last_sort.c utils_4.c \
# 	get_next_line.c get_next_line_utils.c \
# 	actions_2_bonus.c actions_bonus.c
OBG = $(SRCS:.c=.o)
# BONUS_OBG = $(BONUS_SRCS:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
NAME = minishell
# BONUS = checker

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $(CFLAGS) $(OBG) -o $(NAME)

# bonus: $(BONUS)

# $(BONUS): $(BONUS_OBG)
# 	$(CC) $(CFLAGS) $(BONUS_OBG) -o checker

clean:
	rm -rf $(OBG)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re