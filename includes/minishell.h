/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 23:55:07 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h>
# include "shell.h"

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}	t_pids;

typedef struct s_export_vars
{
	int		exit_status;
	int		i;
	char	*curr;
	char	*key;
	char	*eqptr;
	int		key_found;
}	t_xp;

typedef struct s_pipe
{
	int			pipe_fds[2];
	int			input_fd;
	int			last_cmd;
	int			exit_status;
	t_ast_node	*curr;
	t_ast_node	*runcmd;
	pid_t		pid;
	t_pids		*all_pids;
}	t_pipe;

typedef struct s_wait_children_vars
{
	int		status;
	int		final_status;
	t_pids	*curr;
	pid_t	last_pid;
}	t_child_vars;

typedef struct s_build_env
{
	int		i;
	int		j;
	t_env	*node;
	t_env	*last;
}	t_build_env;

typedef struct s_path_vars
{
	int		i;
	char	*paths;
	char	**split_paths;
	char	*full_path;
}	t_path_vars;

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
void	add_pid(t_pids **pids, int pid);
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
void	free_all_pids(t_pids **all_pids);

#endif