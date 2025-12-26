/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:33:55 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 22:57:50 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void	run_child_prcs(t_shell *shell, t_pipe *pv)
{
	if (pv->input_fd != STDIN_FILENO)
	{
		dup2(pv->input_fd, STDIN_FILENO);
		close(pv->input_fd);
	}
	if (!pv->last_cmd)
	{
		close(pv->pipe_fds[0]);
		dup2(pv->pipe_fds[1], STDOUT_FILENO);
		close(pv->pipe_fds[1]);
	}
	run_cmd_no_fork(pv->runcmd, shell);
}

void	run_parent_prcs(t_pipe *pv)
{
	add_pid(&pv->all_pids, pv->pid);
	if (pv->input_fd != STDIN_FILENO)
		close(pv->input_fd);
	if (!pv->last_cmd)
	{
		close(pv->pipe_fds[1]);
		pv->input_fd = pv->pipe_fds[0];
		pv->curr = pv->curr->right;
	}
	else
		pv->curr = NULL;
}

static int init_pipe_stage(t_pipe *pv)
{
	pv->last_cmd = 0;
	if (pv->curr->type == NODE_PIPE)
		pv->runcmd = pv->curr->left;
	else
	{
		pv->runcmd = pv->curr;
		pv->last_cmd = 1;
	}
	if (!pv->last_cmd)
		if (pipe(pv->pipe_fds) == -1)
			return (perror("minishell: pipe"), 1);
	pv->pid = fork();
	if (pv->pid == -1)
	{
		perror("minishell: fork");
		if (!pv->last_cmd)
		{
			close(pv->pipe_fds[0]);
			close(pv->pipe_fds[1]);
		}
		return (1);
	}
	return (0);
}

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	t_pipe	pv;

	pv.all_pids = NULL;
	pv.input_fd = STDIN_FILENO;
	pv.curr = node;
	pv.pid = -1;
	while (pv.curr)
	{
		if (init_pipe_stage(&pv) == 1)
			return (1);
		if (pv.pid == 0)
			run_child_prcs(shell, &pv);		
		run_parent_prcs(&pv);
	}
	pv.exit_status = wait_children(pv.all_pids);
	free_all_pids(&pv.all_pids);
	return (pv.exit_status);
}
