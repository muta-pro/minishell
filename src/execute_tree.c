/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:29:44 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/21 16:57:30 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(t_ast_node *node);

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
	shell->exit_status = status;
	// printf("Exit status: %d\n\n", status);
}

int	execute_builtin(t_ast_node *cmd, t_shell *shell)
{
	int	i;

	if (!strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	if (!strcmp(cmd->args[0], "pwd"))
		return (ft_getcwd());
	if (!strcmp(cmd->args[0], "cd"))
		return (ft_chdir(cmd, shell));
	if (!strcmp(cmd->args[0], "env"))
	{
		ft_env(shell->env_list);
		return (0);
	}
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
		return (ft_exit(cmd, shell->exit_status));
	return (127);
}

int	is_dir(const char *path)
{
	int		fd;
	int		dir;
	char	buffer;

	dir = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, &buffer, 0) == -1 && errno == EISDIR)
		dir = 1;
	close(fd);
	return (dir);
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
	{
		if (access(cmnd, F_OK) == -1)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
			write(STDERR_FILENO, ": No such file or directory\n: ", 30);
			exit(127);
		}
		if (is_dir(cmnd))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			exit(126);
		}
		twoDenv = list_to_2d(shell->env_list);
		execve(cmnd, cmd->args, twoDenv);
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
		write(STDERR_FILENO, ": ", 2);
		perror("");
		free(twoDenv);
		exit(126);
	}
	twoDenv = list_to_2d(shell->env_list);
	path = get_path(twoDenv, cmnd);
	if (path)
	{
		execve(path, cmd->args, twoDenv);
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
		write(STDERR_FILENO, ": ", 11);
		perror("");
		free(twoDenv);
		exit(126);
	}
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
	write(STDERR_FILENO, ": command not found\n", 20);
	free(twoDenv);
	exit(127);
}

// void	execute_external(t_shell *shell, t_ast_node* cmd)
// {
// 	char	**twoDenv;
// 	char	*path;
	
// 	path = NULL;
// 	twoDenv = list_to_2d(shell->env_list);
// 	path = get_path(twoDenv, cmd->args[0]);
// 	if (path == NULL)
// 	{
// 		write(STDERR_FILENO, "minishell:", 10);
// 		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
// 		write(STDERR_FILENO, " : command not found\n", 21);
// 		free_arr(twoDenv);
// 		exit(127);
// 	}
// 	execve(path, cmd->args, twoDenv);
// 	write(STDERR_FILENO, "minishell: ", 11);
// 	write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
// 	write(STDERR_FILENO, ": ", 2);
// 	perror("");
// 	free(path);
// 	exit(126);
// }

// void execute_single_cmd(t_ast_node *cmd, t_env **env)
// {
// 	pid_t	pid;
// 	int		status;

// 	if (is_builtin(cmd))
// 		execute_builtin(cmd, *env);
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			return ;
// 		}

// 		if (pid == 0)
// 		{
// 			if (apply_redir(cmd->redir_list) != 0)
// 				exit(1); // check later
// 			execute_external(*env, cmd);
// 		}
// 		else
// 			waitpid(pid, &status, 0); // deal with status later
// 	}
// }

int	is_parent_lvl_builtin(const char *cmd)
{
	if (strcmp(cmd, "cd") == 0
		|| strcmp(cmd, "export") == 0
		|| strcmp(cmd, "unset") == 0
		||strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
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

void	restore_fds(int ogstdin, int ogstdout)
{
	dup2(ogstdin, STDIN_FILENO);
	dup2(ogstdout, STDOUT_FILENO);
	close(ogstdin);
	close(ogstdout);
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
	{
		restore_fds(og_stdin, og_stdout);
		return (1);
	}
	if (cmd->args && cmd->args[0])
		exit_status = execute_builtin(cmd, shell);
	restore_fds(og_stdin, og_stdout);
	return (exit_status);
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
		{
			perror("minishell: fork");
			return (1);
		}
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
