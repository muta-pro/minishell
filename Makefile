CC = cc

INC_DIR = includes

CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

NAME = minishell

SRC_DIR = src
SRCS_FILES =	main.c \
				builtins.c \
				env.c \
				execute_tree.c \
				pipe.c \
				path.c \
				test.c #delete later
# 				minishell.c \
# 				lexer.c \
# 				scanner.c \
# 				token.c \
# 				tokenizer.c \
# 				utils.c \
# 				quotescan.c \
# 				env.c \
# 				signals.c \
# 				ast.c \
# 				parser.c \
# 				free.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

LIBFTPATH = libft/libft.a

OBJS = $(SRCS_FILES:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(LIBFTPATH)
	$(CC) $(CFLAGS) $(OBJS) -g $(LIBFTPATH) -o minishell -lreadline

$(LIBFTPATH):
	make -C libft/

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all