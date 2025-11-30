/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:41:41 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/30 22:06:53 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

void	print_shell_err(char *src, const char *msg, int exit_code)
{
	(void)exit_code;
	// set_g_exit_status(exit_code);
	WRITE_STR(SHELL_NAME);
	if (src && ft_strlen(src) > 0)
	{
		WRITE_STR(src);
		write(STDERR_FILENO, ": ", 2);
	}
	WRITE_STR(msg);
	write(STDERR_FILENO, "\n", 1);
}

t_ast_node	*ast_err_cleanup(t_ast_node *node, const char *msg)
{
	print_shell_err(SYTX_ERR, msg, 258);
	if (node)
		free_ast(node);
	return (NULL);
}
