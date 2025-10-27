CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline -L/usr/local/opt/readline/lib

INCDIR = include
CPPFLAGS = -I$(INCDIR) -I$(LIBFTDIR) -I/usr/local/opt/readline/include

NAME = minishell
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a


SRCF = minishell.c \
		lexer.c scanner.c \
		token.c tokenizer.c \
		utils.c quotescan.c \
		env.c signlas.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCF))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDE = -I$(INCDIR) -I$(LIBFTDIR) -I.


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(NAME) is ready!"

$(LIBFT):
	@make -sC $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@make -sC $(LIBFTDIR) clean
	@echo "Cleaned obj files"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFTDIR) fclean
	@echo "Cleaned all"

re: fclean all

test: $(NAME)
	@echo "Running $(NAME) -- exit immediately"
	@printf "\x04" | ./$(NAME) && echo "[ OK ]" || echo "[FAILED]"

.PHONY: all clean fclean re test