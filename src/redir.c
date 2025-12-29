/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/07 15:49:06 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/29 17:36:02 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	redir_out_append(t_redir *node)
{
	int	fd;

	if (node->type == T_REDIR_OUT)
		fd = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(node->file_name);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_in(t_redir *node)
{
	int	fd;

	fd = open(node->file_name, O_RDONLY);
	if (fd == -1)
	{
		perror(node->file_name);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redir(t_redir *node)
{
	while (node)
	{
		if (node->type == T_REDIR_OUT || node->type == T_REDIR_APPEND)
		{
			if (redir_out_append(node) == -1)
				return (-1);
		}
		else if (node->type == T_REDIR_IN)
		{
			if (redir_in(node) == -1)
				return (-1);
		}
		node = node->next;
	}
	return (0);
}
