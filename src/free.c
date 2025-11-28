/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:42:53 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 23:37:28 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
#include "shell.h"

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMND)
	{
		free_arr(node->args); //free char**args and strings inside
		free_redirs(node->redir_list);
	}
	free(node);
}

void	free_arr(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_envp(char **envp_cpy)
{
	free_arr(envp_cpy);
}
// void	clear_history();

t_ast_node	*ast_err_cleanup(t_ast_node *node, const char *msg)
{
	print_shell_err(SYTX_ERR, msg, 258);
	if (node)
		free_ast(node);
	return (NULL);
}

void	print_shell_err(char *src, const char *msg, int exit_code)
{
	set_g_exit_status(exit_code);
	WRITE_STR(SHELL_NAME);
	if (src && ft_strlen(src) > 0)
	{
		WRITE_STR(src);
		write(STDERR, ": ", 2);
	}
	WRITE_STR(msg);
	write(STDERR, "\n", 1);
}
// 4. Set Global Exit Status: (Not handled by this function directly, but in the caller)
    // The exit_code argument tells the caller what status to set globally ($?).
