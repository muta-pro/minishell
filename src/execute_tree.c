/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:29:44 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/12 21:37:42 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(t_ast_node *node);

void	execute_AST(t_env *env, t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(env, node);
	else if (node->type == NODE_CMND)
		execute_single_cmd(node, &env);
}

int	execute_builtin(t_ast_node *cmd, t_env **env)
{
	(void)env;

	if (!strcmp(cmd->args[0], "pwd"))
		return (ft_getcwd());
	if (!strcmp(cmd->args[0], "cd"))
		return (ft_chdir(cmd, env));
	if (!strcmp(cmd->args[0], "env"))
	{
		ft_env(*env);
		return (0);
	}	
	if (!strcmp(cmd->args[0], "export"))
		return (ft_export(env, cmd->args[1]), 0);
	if (!strcmp(cmd->args[0], "unset"))
	{
		int i = 1;
		while (cmd->args[i])
		{
			ft_unset(env, cmd->args[i]);
			i++;
		}
		return (0); //fix this
	}
	if (!strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd));
	return (127);
}

void	execute_external(t_env *env, t_ast_node* cmd)
{
	char	**twoDenv;
	char	*path;
	
	path = NULL;
	twoDenv = list_to_2d(env);
	path = get_path(twoDenv, cmd->args[0]);
	if (execve(path, cmd->args, twoDenv) == -1)
	{
		perror("execve");
		free_arr(twoDenv);
		free(path);
		// free_env(&env);
		// free_cmd(&cmd);
		exit(0); // handle exit
	}
}

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

void exec_cmd_in_child(t_ast_node *cmd, t_env **env)
{
	int	exit_code;

	if (apply_redir(cmd->redir_list))
		exit (1);
	if (is_builtin(cmd))
	{
		exit_code = execute_builtin(cmd, env);
		exit(exit_code);
	}
	else
		execute_external(*env, cmd);
}

void	restore_fds(int ogstdin, int ogstdout)
{
	dup2(ogstdin, STDIN_FILENO);
	dup2(ogstdout, STDOUT_FILENO);
	close(ogstdin);
	close(ogstdout);
}

int	exec_builtin_in_parent(t_ast_node *cmd, t_env **env)
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
		exit_status = execute_builtin(cmd, env);
	restore_fds(og_stdin, og_stdout);
	return (exit_status);
}

void	execute_single_cmd(t_ast_node *cmd, t_env **env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		exec_builtin_in_parent(cmd, env);
		return ;
	}
	if (is_parent_lvl_builtin(cmd->args[0]))
		exit_code = exec_builtin_in_parent(cmd, env);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork"); // fix exit status
			return ;
		}
		if (pid == 0)
		{
			exec_cmd_in_child(cmd, env);
		}
		else
		{
			waitpid(pid, &status, 0); // fix exit status;
		}
	}
}