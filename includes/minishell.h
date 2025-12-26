/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 16:23:43 by joko          ########   odam.nl         */
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
int		list_size(t_env *env);
char	**list_to_2d(t_env *env);
char	*find_path(char **split_paths, char *cmd);
char	*get_path(char **twoDenv, char *cmd);
t_env	*add_new_node(void);
void	env_add_last(t_env **env, t_env *new_node);

int		execute_builtin(t_ast_node *cmd, t_shell *shell);
void	set_env_val(t_env **env, const char *key, const char *value);
void    update_if_exists(t_env **env, t_xp *xp);
void    export_new_node(t_env **env, t_xp *xp);
int		valid_id(const char *str);
void    print_export(t_env *env);
void    parse_export_arg(t_ast_node *node, t_xp *xp);

#endif