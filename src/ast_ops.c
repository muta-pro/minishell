/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:58:46 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/22 05:02:41 by imutavdz         ###   ########.fr       */
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

void	redir_add_node(t_redir **head, t_redir *new_node)
{
	t_redir	*last;

	if (!*head)
		*head = new_node;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

t_redir	*init_redir_node(t_token *op, t_token *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = op->type;
	node->file_name = ft_strdup(file->lexeme);
	node->no_expand = 0;
	if (delim_has_qt(node->file_name))
	{
		node->no_expand = 1;
		node->file_name = eliminate_qt(node->file_name);
	}
	node->next = NULL;
	return (node);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	return (res);
}
