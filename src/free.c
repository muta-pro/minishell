/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:42:53 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 16:32:00 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
#include "shell.h"

void	free_ast(t_ast_node *node, const char *msg)
{
	if (!node)
		return ;
	if (msg)
		print_err(SYTX_ERR, msg);
	free_ast(node->left, NULL);
	free_ast(node->right, NULL);
	if (node->type == NODE_CMND)
	{
		free_arr(node->args);//free char**args and strings inside
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
	while (args[i++])
		free(args[i]);
	free(args);
}

void	free_redirs(t_redir *redirs)
{
	t_redir *tmp;
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

void clear_history();