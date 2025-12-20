/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:33:55 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/18 17:32:35 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(t_ast_node *node)
{
	int	i = 0;
	const char *builtins[] = {"echo", "cd", "pwd", "exit", "env", "export", "unset", NULL};
	while (builtins[i])
	{
		if (!strcmp(node->args[0], builtins[i]))
			return 1;
		else
			i++;
	}
	return 0;
}

void	run_cmd_no_fork(t_ast_node *cmd, t_shell *shell)
{
	int	exit_code;

	if (apply_redir(cmd->redir_list) != 0)
		exit (1);
	if (cmd->args == NULL || cmd->args[0] == NULL)
		exit (0);
	if (is_builtin(cmd))
	{
		exit_code = execute_builtin(cmd, shell);
		exit (exit_code);
	}
	else
		execute_external(shell, cmd);
}

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	int			pipe_fds[2];
	int			input_fd;
	int			last_cmd;
	int			exit_status;
	t_ast_node	*curr;
	t_ast_node	*runcmd;
	pid_t		pid;
	t_pids		*all_pids;

	all_pids = NULL;
	input_fd = STDIN_FILENO;
	curr = node;
	pid = -1;
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
			run_cmd_no_fork(runcmd, shell);
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
	exit_status = wait_children(all_pids);
	// free pids?
	return (exit_status);
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

int	wait_children(t_pids *pids)
{
	int		status;
	int		final_status;
	t_pids	*curr;
	pid_t	last_pid;

	last_pid = 0;
	final_status = 0;
	status = 0;
	curr = pids;
	if (curr)
	{
		while (curr->next)
			curr = curr->next;
		last_pid = curr->pid;
	}
	curr = pids;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (curr->pid == last_pid)
			final_status = status;
		curr = curr->next;
	}
	if (WIFEXITED(final_status))
		return (WEXITSTATUS(final_status));
	else if (WIFSIGNALED(final_status))
		return (128 + WTERMSIG(final_status));
	return (0);
}