/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:07:01 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/11/30 17:52:34 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
/*Heredoc handling is complex and involves multiple phases:

Tokenizer: recognize <<
Parser: identify the delimiter
Executor: read lines until delimiter
Expander: expand variables if delimiter wasn't quoted*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_heredoc
{
	char	*delimiter;
	int		expand;
}	t_heredoc;

typedef struct s_shell
{
	t_env	*env_list;
	int		exit_status;
}	t_shell;

# include "defines.h"
# include "token.h"
# include "parser.h"
# include "lexer.h"
# include "sgnl.h"
# include "color.h"
# include "minishell.h"

extern volatile	sig_atomic_t g_got_sigint;

int		init_shlvl(char **envp);
int		update_env_var(char ***envp, char *key, char *value);
char	*new_env_str(char *key, char *value);
int		find_env_varible(char **envp, char *key);
char	*get_env_val(t_env *env, char *key);
void	unset_env_var(char ***envp, char *key);//remove var

// void	print_tokens(t_token *tokens);
//utils
char	*ft_strjoin_free(char *s1, char *s2);
char	*join_char(char *str, char c);
int		delim_has_qt(char *str);
void	handle_sngl_qt(char *arg, int *i, char **res);
void	handle_dollar(char *arg, int *i, char **res, t_shell *shell);


void	here_docs(t_ast_node *node, int *h_count);
void	clean_tmp(t_ast_node *node);
int		is_temp_hfile(char *file_name);

//check characters
int		is_operator_char(char c);
int		is_whitespace(char c);
int		is_quote(char c);
int		is_redirection(char c);
int		valid_char(char c);
int		null_terminator(char c);

//SIGNALS
// static void	install_parent_handler(void);
void	handle_sigint(int sig);
void	handle_sigint_hrdc(int sig);
void	install_parent_handler(void);
void	set_parent_sig_exec(void);

void	debug_ast(t_ast_node *node, int level);
void	print_shell_err(char *type, const char *msg);
void	expand_ast(t_ast_node *node, t_shell *shell);
char	*substitute_and_clean(char *arg, t_shell *shell);
char	*get_var_value(char *str, int *i, t_shell *shell);

#endif