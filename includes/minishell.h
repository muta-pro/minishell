/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 23:55:07 by imutavdz      ########   odam.nl         */
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

typedef struct s_env		t_env;
typedef struct s_ast_node	t_ast_node;

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

#endif