/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/12 21:37:32 by yneshev       ########   odam.nl         */
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
# include "shell.h"

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}	t_pids;


int		ft_getcwd();
int		ft_chdir(t_ast_node *cmd, t_env **env);
int		ft_exit(t_ast_node *cmd);
void	ft_env(t_env *env);
void	ft_unset(t_env **env, char *str);
void	ft_export(t_env **env, char *str);
void	free_env(t_env **env);
void	free_arr(char **arr);
void	exec_pipe(t_env *env, t_ast_node *node);
void	add_pid(t_pids **pids, int pid);
void	wait_children(t_pids *pids, pid_t pid);
void	build_env(char **envp, t_env **env);
void	execute_AST(t_env *env, t_ast_node *node);
void	execute_single_cmd(t_ast_node *cmd, t_env **env);
void	execute_external(t_env *env, t_ast_node* cmd);
int		apply_redir(t_redir *node);
int		list_size(t_env *env);
char	**list_to_2d(t_env *env);
char	*find_path(char **split_paths, char *cmd);
char	*get_path(char **twoDenv, char *cmd);
t_env	*add_new_node(void);

int	execute_builtin(t_ast_node *cmd, t_env **env);
void	set_env_val(t_env **env, const char *key, const char *value);

#endif