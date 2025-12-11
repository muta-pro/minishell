/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/05 15:45:03 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:11:07 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//LEXICAL ANALYSIS
//TEST :
//cat file | grep word
//echo hello > output.txt
#include "shell.h"

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

int	is_redir_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_APPEND || token->type == T_REDIR_HEREDOC);
}

t_token	*create_token(t_tok_type type, const char *lexeme)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (lexeme)
		token->lexeme = ft_strdup(lexeme);
	else
		token->lexeme = NULL;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	insert_token(t_token **head, t_token *new_token)
{
	t_token	*curr;

	if (!new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_token;
	}
}
// nospace_oper();
