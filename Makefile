CC = cc

INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -g


NAME = minishell
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRC_DIR = src
SRCS_FILES =	builtins.c \
				ast.c \
				ast_ops.c \
				char_class.c \
				char_ops.c \
				token.c \
				env.c \
				execute_tree.c \
				expand_tree.c \
				free.c \
				lexer.c \
				utils.c \
				quotescan.c \
				signals.c \
				parser.c \
				scanner.c \
				tokenizer.c \
				pipe.c \
				path.c \
				error.c \
				redir.c \
				minishell.c \
				main.c \
				here_docs.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)
INCLUDE = -I$(INC_DIR) -I ./$(LIBFTDIR) -I.

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -g $(LIBFT) -o minishell -lreadline

$(LIBFT):
	@make -sC $(LIBFTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

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