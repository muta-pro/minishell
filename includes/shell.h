/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:07:01 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/12 17:31:12 by yneshev       ########   odam.nl         */
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

# include "token.h"
# include "defines.h"
# include "parser.h"
# include "lexer.h"
# include "sgnl.h"
# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env		*env_list;
	int			exit_status;
	int			save_exit_status;
	t_token		*curr_tok;
	t_ast_node	*curr_ast;
	int			should_exit;
}				t_shell;

int			run_ast(t_ast_node *ast, t_shell *shell);
t_ast_node	*build_ast(char *line, t_token **tok, t_shell *shell);
void		cleanup_pack(char *line, t_token *tok, t_ast_node *ast);
void		child_cleanup_exit(t_shell *shell, int code);


int			init_shlvl(char **envp);
int			update_env_var(char ***envp, char *key, char *value);
char		*new_env_str(char *key, char *value);
int			find_env_varible(char **envp, char *key);
char		*get_env_val(t_env *env, const char *key);

//utils
char		*ft_strjoin_free(char *s1, char *s2);
char		*join_char(char *str, char c);
int			delim_has_qt(char *str);
void		handle_sngl_qt(char *arg, int *i, char **res);
void		handle_dollar(char *arg, int *i, char **res, t_shell *shell);


int			here_docs(t_ast_node *node, int *h_count, t_shell *shell);
void		expand_h_line(char **line, int no_expand, t_shell *shell);
void		clean_tmp(t_ast_node *node);
int			is_tmp_hfile(char *file_name);

//check characters
int			is_operator_char(char c);
int			is_whitespace(char c);
int			is_quote(char c);
int			is_redirection(char c);
int			valid_char(char c);
int			null_terminator(char c);

//SIGNALS
void		handle_sigint(int sig);
void		handle_sigint_hrdc(int sig);
void		install_parent_handler(void);
void		set_parent_sig_exec(void);
void		child_sig_handler(void);

void		debug_ast(t_ast_node *node, int level);
void		print_shell_err(char *type, const char *msg);
void		print_eof_warning(char *delim);
void		expand_ast(t_ast_node *node, t_shell *shell);
char		*expand_h_var(char *line, t_shell *shell);
char		*substitute_and_clean(char *arg, t_shell *shell);
char		*get_var_value(char *str, int *i, t_shell *shell);
//EXEC
int		ft_getcwd();
int		ft_cd(t_ast_node *cmd, t_shell *shell);
int		ft_exit(t_ast_node *cmd, t_shell *shell);
void	ft_env(t_env *env);
void	ft_unset(t_env **env, char *str);
int		ft_export(t_env **env, t_ast_node *node);
void	free_env(t_env **env);
void	free_arr(char **arr);
int		exec_pipe(t_shell *shell, t_ast_node *node);
int		is_dir(const char *path);
int		ft_echo(char **args);
int		add_pid(t_pids **pids, int pid);
int		wait_children(t_pids *pids);
void	build_env(char **envp, t_env **env);
void	execute_ast(t_shell *shell, t_ast_node *node);
int		execute_single_cmd(t_ast_node *cmd, t_shell *shell);
void	execute_external(t_shell *shell, t_ast_node* cmd);
int		apply_redir(t_redir *node);
int		apply_redir_parent(t_redir *node);
int		list_size(t_env *env);
char	**list_to_2d(t_env *env);
char	*find_path(char **split_paths, char *cmd);
char	*get_path(char **twoDenv, char *cmd);
t_env	*add_new_node(void);
void	env_add_last(t_env **env, t_env *new_node);

int		execute_builtin(t_ast_node *cmd, t_shell *shell);
int		set_env_val(t_env **env, const char *key, const char *value);
void    update_if_exists(t_env **env, t_xp *xp);
void    export_new_node(t_env **env, t_xp *xp);
int		valid_id(const char *str);
int		is_parent_lvl_builtin(const char *cmd);
int		is_builtin(t_ast_node *node);
int		exec_builtin_in_parent(t_ast_node *cmd, t_shell *shell);
void	restore_fds(int ogstdin, int ogstdout);
void    print_export(t_env *env);
void    parse_export_arg(t_ast_node *node, t_xp *xp);
void	handle_exec_errors(t_shell *shell, t_ast_node *cmd, char *cmnd);
void	exec_external_print_err(char *cmnd);
void	cmd_not_found(char *cmnd);
void	free_all_pids(t_pids **all_pids);

#endif
