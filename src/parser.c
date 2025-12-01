/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:54 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/01 16:47:26 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
implement recursive descent parser approach
Start the main parsing routine, checking for the highest precedence first
parse_cmnd : scans until hits pipe, op or EOF;
have args arr to hold words
detect * function and expand into filenames. <<<<<
*/
#include "shell.h"

t_ast_node	*parser(t_token *token)
{
	return (parse_logic_op(&token));
}

t_ast_node	*parse_logic_op(t_token **tokens)
{
	t_ast_node		*node;
	t_ast_node		*left;
	t_tok_type		type;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (peek_tok(*tokens) && (peek_tok(*tokens)->type == T_LOGIC_OR
			|| peek_tok(*tokens)->type == T_LOGIC_AND))
	{
		type = peek_tok(*tokens)->type;
		consume_tok(tokens, type);
		if (type == T_LOGIC_OR)
			node = create_ast_nd(NODE_OR, left, NULL);
		else
			node = create_ast_nd(NODE_AND, left, NULL);
		node->right = parse_pipeline(tokens);
		left = node;
		if (!left->right)
		{
			free_ast(node);
			return (NULL);
		}
	}
	return (left);
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*node;

	left = parse_cmnd(tokens);
	if (!left)
		return (NULL);
	while (peek_tok(*tokens) && peek_tok(*tokens)->type == T_PIPE)
	{
		consume_tok(tokens, T_PIPE);
		node = create_ast_nd(NODE_PIPE, left, NULL);
		node->right = parse_cmnd(tokens);
		left = node;
		if (!left->right)
		{
			free_ast(node);
			free_ast(left);
			return (NULL);
		} //SYNTAX ERR pipe no cmnd
	}
	return (left);
}

t_ast_node	*parse_cmnd(t_token **tokens)
{
	t_ast_node	*node;
	char		**args;
	t_redir		*redirs;

	redirs = NULL;
	args = NULL;
	while (peek_tok(*tokens)
		&& peek_tok(*tokens)->type != T_EOF
		&& peek_tok(*tokens)->type != T_PIPE
		&& peek_tok(*tokens)->type != T_LOGIC_OR
		&& peek_tok(*tokens)->type != T_LOGIC_AND)
	{
		args_redirs_tok(tokens, &args, &redirs);
	}
	if (!args && !redirs)
		return (NULL);
	node = create_ast_nd(NODE_CMND, NULL, NULL);
	node->args = args;
	node->redir_list = redirs;
	return (node);
}

void	parse_redir(t_token **tokens, t_redir **redir_head)
{
	t_redir	*new_node;
	t_redir	*last;
	t_token	*op;
	t_token	*file;

	op = consume_tok(tokens, peek_tok(*tokens)->type);
	file = consume_tok(tokens, T_WORD);
	if (!file)
		file = consume_tok(tokens, T_STR);
	if (!file)
		return (print_shell_err(SYTX_ERR, "unexpected token.", 258));
	new_node = malloc(sizeof(t_redir));
	new_node->type = op->type;
	new_node->file_name = strdup(file->lexeme);
	new_node->next = NULL;
	if (!*redir_head)
		*redir_head = new_node;
	else
	{
		last = *redir_head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}
//malloc and init new ast_nd
