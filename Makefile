CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDGLAGS = -lreadline -L/usr/local/opt/readline/lib
CPPFLAGS = -Include -Ilibft -I/usr/local/opt/readline/include

NAME = minishell
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft

SRCF = minishell.c \
		lexer.c scanner.c \
		token.c tokenizer.c \
		utils.c quotescan.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCF))
OBJS = $(addprefix $(OBJDIR)/, $(SRCF: .c=.o))
INCLUDE = -I$(INCDIR) -I$(LIBFTDIR) -I.

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC_FILES))

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(NAME) is ready!"

$(LIBFT):
	make -sC $(LIBFTDIR)

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