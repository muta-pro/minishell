/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 22:56:14 by joko          #+#    #+#                 */
/*   Updated: 2025/12/29 17:20:38 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_pid(t_pids **pids, int pid)
{
	t_pids	*new;
	t_pids	*current_node;

	new = malloc(sizeof(*new));
	if (!new)
		return (0);
	new->pid = pid;
	new->next = NULL;
	if (!*pids)
		return (*pids = new, 1);
	current_node = *pids;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = new;
	return (1);
}

int	is_builtin(t_ast_node *node)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd", "exit", "env", "export", "unset", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(node->args[0], builtins[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

void	free_all_pids(t_pids **all_pids)
{
	t_pids	*temp;

	temp = *all_pids;
	while (*all_pids)
	{
		temp = *all_pids;
		*all_pids = (*all_pids)->next;
		free(temp);
	}
}

static int	decode_wait_stat(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	wait_children(t_pids *pids)
{
	t_pids	*last;
	int		st;
	int		last_st;

	last = pids;
	while (last && last->next)
		last = last->next;
	last_st = 0;
	while (pids)
	{
		waitpid(pids->pid, &st, 0);
		if (last && pids->pid == last->pid)
			last_st = st;
		pids = pids->next;
	}
	return (decode_wait_stat(last_st));
}
