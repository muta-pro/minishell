/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:29:44 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/29 18:10:00 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_ast(t_shell *shell, t_ast_node *node)//???
{
	int	status;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		status = exec_pipe(shell, node);
	else
		status = execute_single_cmd(node, shell);
	shell->exit_status = status;
	if (status == -42)
		shell->exit_status = -42;
}

void	execute_external(t_shell *shell, t_ast_node *cmd)
{
	char	**two_d_env;
	char	*path;
	char	*cmnd;

	cmnd = cmd->args[0];
	path = NULL;
	if (!cmnd || *cmnd == '\0')
	{
		cmd_not_found("");
		child_cleanup_exit(shell, 127);
	}
	if (ft_strchr(cmnd, '/'))
		handle_exec_errors(shell, cmd, cmnd);
	two_d_env = list_to_2d(shell->env_list);
	path = get_path(two_d_env, cmnd);
	if (!path)
		return (cmd_not_found(cmnd), free_arr(two_d_env),
			child_cleanup_exit(shell, 127));
	child_sig_handler();
	execve(path, cmd->args, two_d_env);
	exec_external_print_err(cmnd);
	free(path);
	free_arr(two_d_env);
	child_cleanup_exit(shell, 126);
}

void	exec_cmd_in_child(t_ast_node *cmd, t_shell *shell)
{
	int	exit_code;

	if (apply_redir(cmd->redir_list))
		child_cleanup_exit(shell, 1);
	if (is_builtin(cmd))
	{
		exit_code = execute_builtin(cmd, shell);
		if (exit_code == -42)
			exit_code = shell->save_exit_status;
		child_cleanup_exit(shell, exit_code);
	}
	execute_external(shell, cmd);
}

static int	wait_and_getstatus(pid_t pid)
{
	int	status;

	set_parent_sig_exec();
	waitpid(pid, &status, 0);
	install_parent_handler();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		write (1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_single_cmd(t_ast_node *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd->args || !cmd->args[0])
	{
		if (apply_redir_parent(cmd->redir_list))
			return (1);
		return (0);
	}
	if (is_parent_lvl_builtin(cmd->args[0]))
		return (exec_builtin_in_parent(cmd, shell));
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			exec_cmd_in_child(cmd, shell);
		return (wait_and_getstatus(pid));
	}
}
