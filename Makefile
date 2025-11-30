CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC_DIR = src
SRCS_FILES =	main.c \
				builtins.c \
				env.c \
				execute_tree.c \
				pipe.c \
				path.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

LIBFTPATH = libft/libft.a

OBJS = $(SRCS_FILES:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(LIBFTPATH)
	$(CC) $(OBJS) -g $(LIBFTPATH) -o minishell -lreadline

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