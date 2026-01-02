/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:33:55 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/29 17:18:33 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	run_cmd_no_fork(t_ast_node *cmd, t_shell *shell)
{
	int	exit_code;

	if (apply_redir(cmd->redir_list) != 0)
		child_cleanup_exit(shell, 1);
	if (!cmd->args || !cmd->args[0])
		child_cleanup_exit(shell, 0);
	if (is_builtin(cmd))
	{
		exit_code = execute_builtin(cmd, shell);
		child_cleanup_exit(shell, exit_code);
	}
	execute_external(shell, cmd);
	child_cleanup_exit(shell, 127);
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

void	run_parent_prcs(t_shell *shell, t_pipe *pv)
{
	if (!add_pid(&pv->all_pids, pv->pid))
	{
		perror("minishell: malloc");
		shell->exit_status = 1;
		pv->curr = NULL;
		return ;
	}
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

static int	init_pipe_stage(t_pipe *pv)
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
	set_parent_sig_exec();
	while (pv.curr)
	{
		if (init_pipe_stage(&pv) == 1)
			return (install_parent_handler(), 1);
		if (pv.pid == 0)
			run_child_prcs(shell, &pv);
		run_parent_prcs(shell, &pv);
	}
	pv.exit_status = wait_children(pv.all_pids);
	install_parent_handler();
	free_all_pids(&pv.all_pids);
	return (pv.exit_status);
}
