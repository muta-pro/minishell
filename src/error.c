/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 14:41:41 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:00 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_shell_err(char *src, const char *msg, int exit_code)
{
	if (exit_code != -1)
		g_exit_status = exit_code;
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (src && ft_strlen(src) > 0)
	{
		write(STDERR_FILENO, src, ft_strlen(src));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

t_ast_node	*ast_err_cleanup(t_ast_node *node, const char *msg)
{
	print_shell_err(SYTX_ERR, msg, 258);
	if (node)
		free_ast(node);
	return (NULL);
}
