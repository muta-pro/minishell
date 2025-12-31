/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 21:57:22 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/30 19:01:58 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execute_builtin(t_ast_node *cmd, t_shell *shell)
{
	int	i;

	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_getcwd());
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, shell));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(shell->env_list), 0);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(&shell->env_list, cmd), 0);
	if (!ft_strcmp(cmd->args[0], "unset"))
	{
		i = 1;
		while (cmd->args[i])
		{
			ft_unset(&shell->env_list, cmd->args[i]);
			i++;
		}
		return (0);
	}
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd, shell));
	return (127);
}

int	is_parent_lvl_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin_in_parent(t_ast_node *cmd, t_shell *shell)
{
	int	og_stdin;
	int	og_stdout;
	int	exit_status;

	exit_status = 0;
	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	if (og_stdin == -1 || og_stdout == -1)
		return (perror("minishell: dup"), 1);
	if (apply_redir_parent(cmd->redir_list) == -1)
		return (restore_fds(og_stdin, og_stdout), 1);
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		restore_fds(og_stdin, og_stdout);
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		exit_status = ft_exit(cmd, shell);
		restore_fds(og_stdin, og_stdout);
		return (exit_status);
	}
	exit_status = execute_builtin(cmd, shell);
	restore_fds(og_stdin, og_stdout);
	return (exit_status);
}

void	restore_fds(int ogstdin, int ogstdout)
{
	dup2(ogstdin, STDIN_FILENO);
	dup2(ogstdout, STDOUT_FILENO);
	close(ogstdin);
	close(ogstdout);
}
