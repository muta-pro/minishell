/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 22:56:14 by joko          #+#    #+#                 */
/*   Updated: 2025/12/26 22:57:19 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int	wait_children(t_pids *pids)
{
	t_child_vars	ch;

	ch.last_pid = 0;
	ch.final_status = 0;
	ch.status = 0;
	ch.curr = pids;
	if (ch.curr)
	{
		while (ch.curr->next)
			ch.curr = ch.curr->next;
		ch.last_pid = ch.curr->pid;
	}
	ch.curr = pids;
	while (ch.curr)
	{
		waitpid(ch.curr->pid, &ch.status, 0);
		if (ch.curr->pid == ch.last_pid)
			ch.final_status = ch.status;
		ch.curr = ch.curr->next;
	}
	if (WIFEXITED(ch.final_status))
		return (WEXITSTATUS(ch.final_status));
	else if (WIFSIGNALED(ch.final_status))
		return (128 + WTERMSIG(ch.final_status));
	return (0);
}
