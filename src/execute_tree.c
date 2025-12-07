/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:29:44 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/07 17:07:36 by yneshev       ########   odam.nl         */
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

void	execute_builtin(t_ast_node *cmd, t_env *env)
{
	(void)env;
	if (!strcmp(cmd->args[0], "pwd"))
		ft_getcwd();
	if (!strcmp(cmd->args[0], "cd"))
		ft_chdir(cmd, env);
	if (!strcmp(cmd->args[0], "env"))
		ft_env(env);
	if (!strcmp(cmd->args[0], "export"))
		ft_export(&env, cmd->args[1]);
	if (!strcmp(cmd->args[0], "unset"))
	{
		ft_env(env);
		printf("\n\n\n");
		ft_unset(&env, cmd->args[1]);
		ft_env(env);
	}

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
		// free_arr(twoDenv);
		// free(path);
		// free_env(&env);
		// free_cmd(&cmd);
		exit(0); // handle exit
	}
}

void execute_single_cmd(t_ast_node *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd))
		execute_builtin(cmd, *env);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}

		if (pid == 0)
		{
			if (apply_redir(cmd->redir_list) != 0)
				exit(1); // check later
			execute_external(*env, cmd);
		}
		else
			waitpid(pid, &status, 0); // deal with status later
	}
}

// void	execute_single_cmd(t_ast_node *cmd, t_env *env)
// {
// 	int	i = 0;
// 	const char *builtins[] = {"cd", "pwd", "exit", "env", "export", "unset", NULL};
// 	while (builtins[i])
// 	{
// 		if (!strcmp(cmd->args[0], builtins[i]))
// 		{
// 			execute_builtin(cmd, env);
// 			break ;
// 		}
// 		else
// 			execute_external(env, cmd);
// 		i++;
// 	}
// }

