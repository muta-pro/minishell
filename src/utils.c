/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/13 15:05:05 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:11:14 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void debug_ast(t_ast_node *node, int level)
{
	if (!node)
		return ;
	for (int i = 0; i < level; i++) printf(" ");
		if (node->type == NODE_PIPE)
			printf("\033[1;31m[| PIPE]\033[0m\n");
		else if (node->type == NODE_CMND)
		{
			printf("\033[1;32m[CMD]\033[0m ");
			if (node->args && node->args[0])
				printf("%s\n", node->args[0]);
				else
					printf("empty\n");
				return ;
		}
		for (int i = 0; i < level; i++) printf(" ");
			printf("L-> ");
		debug_ast(node->left, level + 1);
		for (int i = 0; i < level; i++) printf(" ");
			printf("R-> ");
		debug_ast(node->right, level + 1);
}