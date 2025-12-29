/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 21:57:22 by joko          #+#    #+#                 */
/*   Updated: 2025/12/26 21:59:40 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execute_builtin(t_ast_node *cmd, t_shell *shell)
{
	int	i;

	if (!strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	if (!strcmp(cmd->args[0], "pwd"))
		return (ft_getcwd());
	if (!strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, shell));
	if (!strcmp(cmd->args[0], "env"))
		return (ft_env(shell->env_list), 0);
	if (!strcmp(cmd->args[0], "export"))
		return (ft_export(&shell->env_list, cmd), 0);
	if (!strcmp(cmd->args[0], "unset"))
	{
		i = 1;
		while (cmd->args[i]) // Need to pass the whole args array
		{
			ft_unset(&shell->env_list, cmd->args[i]);
			i++;
		}
		return (0); //fix this
	}
	if (!strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd, shell));
	return (127);
}

int	is_parent_lvl_builtin(const char *cmd)
{
	if (strcmp(cmd, "cd") == 0
		|| strcmp(cmd, "export") == 0
		|| strcmp(cmd, "unset") == 0
		||strcmp(cmd, "exit") == 0)
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
	if (apply_redir(cmd->redir_list) != 0)
		return (restore_fds(og_stdin, og_stdout), 1);
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		restore_fds(og_stdin, og_stdout);
		return (0);
	}
	if (strcmp(cmd->args[0], "exit") == 0)
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
