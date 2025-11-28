/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:42:05 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 18:39:56 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

t_token	*peek_tok(t_token *tokens)
{
	return (tokens);
}

t_token	*consume_tok(t_token **tokens, t_tok_type expected)
{
	t_token	*curr;

	curr = *tokens;
	if (!curr || curr->type != expected)
		return (NULL); //syntax err handle later
	*tokens = curr->next;
	return (curr);
}

t_ast_node	*create_ast_nd(t_node_t type, t_ast_node *l, t_ast_node *r)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = l;
	node->right = r;
	node->args = NULL;
	node->redir_list = NULL;
	return (node);
}

void	append_args(char ***args, char *new_arg)
{
	int		count;
	char	**new_list;
	int		i;

	count = 0;
	if (*args)
	{
		while ((*args)[count])
			count++;
		new_list = malloc(sizeof(char *) * (count + 2));
		i = 0;
		while (i < count)
		{
			new_list[i] = (*args)[i];
			i++;
		}
		new_list[i] = strdup(new_arg);
		new_list[i + 1] = NULL;
		if (*args)
			free(*args);
		*args = new_list;
	}
}

int	is_redir_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_APPEND || token->type == T_REDIR_HEREDOC);
}
