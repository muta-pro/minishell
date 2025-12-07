/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:33:55 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/07 17:13:50 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(t_ast_node *node)
{
	int	i = 0;
	const char *builtins[] = {"cd", "pwd", "exit", "env", "export", "unset", NULL};
	while (builtins[i])
	{
		if (!strcmp(node->args[0], builtins[i]))
			return 1;
		else
			i++;
	}
	return 0;
}

void	run_cmd_no_fork(t_ast_node *cmd, t_env *env)
{
	if (is_builtin(cmd))
	{
		execute_builtin(cmd, env);
		exit(0); // fix this
	}
	if (apply_redir(cmd->redir_list) == 0)		// CHECK IF CORRECT
		execute_external(env, cmd);
	else
		exit (1);
}

void	exec_pipe(t_env *env, t_ast_node *node)
{
	int			pipe_fds[2];
	int			input_fd;
	int			last_cmd;
	t_ast_node	*curr;
	t_ast_node	*runcmd;
	pid_t		pid;
	t_pids		*all_pids;

	all_pids = NULL;
	input_fd = STDIN_FILENO;
	curr = node;
	while (curr)
	{
		last_cmd = 0;
		if (curr->type == NODE_PIPE)
			runcmd = curr->left;
		else
		{
			runcmd = curr;
			last_cmd = 1;
		}
		if (!last_cmd)
			if (pipe(pipe_fds) == -1)
				printf("fix this"); // fix this
		pid = fork();
		if (pid == -1)
			printf("fix tihs"); // fix this

		// Child process	
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (!last_cmd)
			{
				close(pipe_fds[0]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			run_cmd_no_fork(runcmd, env);
		}
		
		// Parent process
		add_pid(&all_pids, pid);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (!last_cmd)
		{
			close(pipe_fds[1]);
			input_fd = pipe_fds[0];
			curr = curr->right;
		}
		else
			curr = NULL;
	}

	// Wait for children
	wait_children(all_pids, pid);
}

void add_pid(t_pids **pids, int pid)
{
	t_pids	*new;
	t_pids	*current_node;

	current_node = *pids;

	new = malloc(sizeof(t_pids));
	if (!new)
		printf("fix"); // fix
	new->pid = pid;
	new->next = NULL;
	if (*pids == NULL)
		*pids = new;
	else
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new;
	}
	
}

void	wait_children(t_pids *pids, pid_t pid)
{
	int		status;
	t_pids *curr;

	status = 0;
	curr = pids;
	while (curr)
	{
		if (curr->pid == pid)
			waitpid(curr->pid, &status, 0);
		else
			waitpid(curr->pid, NULL, 0);
		curr = curr->next;
	}
}