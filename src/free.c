/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/28 11:42:53 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:22 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
// void	clear_history();

void	free_tok(t_token *tok)
{
	t_token	*tmp;

	while (tok != NULL)
	{
		tmp = tok->next;
		free(tok->lexeme);
		free(tok);
		tok = tmp;
	}
}

// 4. Set Global Exit Status: (Not handled by this function directly, but in the caller)
    // The exit_code argument tells the caller what status to set globally ($?).
