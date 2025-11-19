/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:54 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/19 16:06:14 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
implement recursive descent parser approach
*/
#include "parser.h"
#include "shell.h"

t_ast_node	parser(char *tokens)
{// Start the main parsing routine, checking for the highest precedence first
	return (parse_logic_op(&tokens));
}

t_ast_node parse_logic_op(t_token **tokens)
{
	t_ast_node	*node;
	t_ast_node	*left;
	t_tok_type		*type;

	left = parse_pipilne(tokens);
	if (!left)
		return (NULL);
	while (peek_tok(*tokens)->type = T_LOGIC_OR || peek_tok(*tokens)->type == T_LOGIC_AND
		|| peek_tok(*tokens))
	{
		type = peek_tok(*tokens)->type;
		consume_tok(tokens, type);
		if (type == T_LOGIC_OR)
			node = create_ast_nd(NODE_AND, left, NULL);
		else
			node = create_ast_nd(NODE_OR, left, NULL);
		node->right = parse_pipilne(tokens);
		left = node;
		if (!left->right)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_pipilne(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*node;

	left = parse_cmnd(tokens);
	if (!left)
		return (NULL);
	if (peek_tok(*tokens) && peek_tok(*tokens)->type = T_PIPE);
	{
		consume_tok(tokens, T_PIPE);
		node = create_ast_nd(NODE_PIPE, left_cmnd, NULL);
		node->right = parse_cmnd(tokens);
		left = node;
		if (!left->right)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_cmnd(t_token **tokens)
{
	t_ast_node	*node;
	char		**args; //array holding words
	t_redir		*redirs; //LL of redirs

	redirs = NULL;
	args = NULL;
	while (peek_tok(*tokens)->type != T_EOF &&
		peek_tok(*tokens)->type != T_PIPE &&
		peek_tok(*tokens)->type != T_LOGIC_OR &&
		peek_tok(*tokens)->type != T_LOGIC_AND)
	{
		if (is_redir_token(peek_tok(*tokens)))
			parse_redir(tokens, &redir_head);
		else if (peek_tok(*tokens)->type == T_WORD || peek_tok(*tokens)->type == T_STR
			|| peek_tok(*tokens)->type == T_VAR)
		{
			append_args(&args, peek_tok(*tokens)->lexeme);
			consume_tok(tokens, peek_tok(*tokens)->type);
		}
		else
			consume_tok(tokens, peek_tok(*tokens)->type);
	}
	if (!args && !node)
		return (print_sntx_err("just redir"));
	node = create_ast_nd(NODE_CMND, NULL, NULL);
	node->args = args;
	node->redir_list = redirs;
	return (node);
}

void parse_redir(t_token tokens **tokens, t_redir **redir_head)
{
	t_redir *new_node;
	t_redir *last;
	t_token *op;
	t_token *file;

	op = consume_tok(tokens, peek_tok(*tokens)->type);
	file = consume_tok(tokens, T_WORD);
	if (!file)
		file = consume_tok(tokens, T_STR);
	if (!file)
	{
		printf("syntax error near unexpected token\n");
		return ;
	}
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







