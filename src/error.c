/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 14:41:41 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:00 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_shell_err(char *src, const char *msg)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (src && ft_strlen(src) > 0)
		write(STDERR_FILENO, src, ft_strlen(src));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

int	free_on_err(char *line, t_token *tokens, t_ast_node *ast)
{
	if (ast)
		free_ast(ast);
	if (tokens)
		free_tok(tokens);
	if (line)
		free(line);
	return (1);
}

void	print_eof_warning(char *delim)
{
	(void)delim;
	ft_putstr_fd(
		"minishell: Warning: here-document delimited by EOF (wanted ", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd(")", 2);
}
