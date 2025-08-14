CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRCS = minishell.c

LIBFTPATH = libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPATH)
	cc $(SRCS) $(LIBFTPATH) -o minishell -lreadline

$(LIBFTPATH):
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

test: $(NAME)
	@echo "Running $(NAME) -- exit immediately"
	@printf "\x04" | ./$(NAME) && echo "[ OK ]" || echo "[FAILED]"

.PHONY: all clean fclean re test