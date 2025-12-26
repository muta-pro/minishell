/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:29:44 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 22:16:52 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_ast(t_shell *shell, t_ast_node *node)
{
	int	status;

	status = shell->exit_status;
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		status = exec_pipe(shell, node);
	else if (node->type == NODE_CMND)
		status = execute_single_cmd(node, shell);
	if (status == -42)
		shell->save_exit_status = shell->exit_status;
	shell->exit_status = status;
}

void	execute_external(t_shell *shell, t_ast_node *cmd)
{
	char	**twoDenv;
	char	*path;
	char	*cmnd;

	cmnd = cmd->args[0];
	path = NULL;
	if (cmnd == NULL || *cmnd == '\0')
		exit(0);
	if (ft_strchr(cmnd, '/'))
		handle_exec_errors(shell, cmd, cmnd);
	twoDenv = list_to_2d(shell->env_list);
	path = get_path(twoDenv, cmnd);
	if (path)
	{
		execve(path, cmd->args, twoDenv);
		exec_external_print_err(cmnd);
		free(twoDenv);
		exit(126);
	}
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
	write(STDERR_FILENO, ": command not found\n", 20);
	free_arr(twoDenv);
	exit(127);
}

void exec_cmd_in_child(t_ast_node *cmd, t_shell *shell)
{
	int	exit_code;

	if (apply_redir(cmd->redir_list))
		exit (1);
	if (is_builtin(cmd))
	{
		exit_code = execute_builtin(cmd, shell);
		exit(exit_code);
	}
	else
		execute_external(shell, cmd);
}

int	execute_single_cmd(t_ast_node *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (exec_builtin_in_parent(cmd, shell));
	if (is_parent_lvl_builtin(cmd->args[0]))
		return (exec_builtin_in_parent(cmd, shell));
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			exec_cmd_in_child(cmd, shell);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status)); // ??
			else if (WIFSIGNALED(status))
				return (128 + WTERMSIG(status));
		}
	}
	return (1);
}
