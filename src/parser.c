/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:54 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/19 14:47:09 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
implement recursive descent parser approach
*/
#include "parser.h"

build_ast(pipe, redirection, cmnd);

t_ast_node	parser(char *tokens)
{// Start the main parsing routine, checking for the highest precedence first
	return (parse_pipilne(&tokens));
	// t_token	*tok;

	// init_lex();
	// tok = next_token();
	// pars_tok(tok)
	// free_tok(&tok);
	// return(ast);
}
t_ast_node parse_logic_op(t_token **tokens)
{
	t_ast_node	*node;
	t_token		*op;

	node = node = parse_pipilne(tokens);
	if (!node)
		return (NULL);
	while (peek(*tokens)->type = T_LOGIC_OR || peek(*tokens)->type == T_LOGIC_OR)
	{
		op = consume_tok(tokens, peek(*tokens)->type);
		if (op->type == T_LOGIC_OR)
			node = create_ast_nd(NODE_AND, node, NULL);
		else
			node = create_ast_nd(NODE_OR, node, NULL);
		node->right = parse_pipilne(tokens);
		if (!node->right)
		{
			print_sntx_err("missing cmnd afteoperator")
			free(tree);
			return (NULL);
		}
	}
	return (node);
}

t_ast_node	parse_pipilne(t_token **tokens)
{
	t_ast_node	*left_cmnd;
	t_ast_node	*pipe_node;

	left_cmnd = parse_cmnd(tokens);
	if (!left_cmnd)
		return (NULL);
	if (peek_tok(*tokens)->type = T_PIPE);
	{
		consume_tok(tokens, T_PIPE);
		pipe_node = create_ast_nd(NODE_PIPE, left_cmnd, NULL);
		pipe_node->right = parse_pipilne(tokens);
		if (!pipe_node->right)
		{
			return (NULL);
		}
		return (pipe_node);
	}
	return (left_cmnd);
}

t_ast_node	*parse_cmnd(t_token **tokens)
{
	t_ast_node	*cmnd_nd;
	char		**args; //array holding words
	t_redir		*redirs; //LL of redirs

	redirs = NULL;
	args = NULL;
	while (peek(*tokens)->type != T_EOF &&
		peek(*tokens)->type != T_PIPE &&
		peek(*tokens)->type != T_LOGIC_OR &&
		peek(*tokens)->type != T_LOGIC_AND)
	{
		if (is_redir_token(peek(*tokens)))
		{
			redir_head = parse_redir(tokens, redir_head);
			parse_redir(tokens, &redir_head);
		}
		else
		{
			args = add_args(args, consume_tok(tokens, ...)->lexeme);
			consume_tok(tokens, peek(*tokens)->type);
		}
	}
	if (!args && !cmnd_nd)
		return (print_sntx_err("just redir"));
	cmnd_nd = create_ast_nd(NODE_CMND, NULL, NULL);
	cmnd_nd->args = args;
	cmnd_nd->redir_list = redir_head;
	return (cmnd_nd);
}

//malloc and init new ast_nd
t_ast_node	*create_ast_nd(t_node_t type, t_ast_node *l, t_ast_node *r); 
t_redir		*parse_redir(t_token **tokens);
//manage token list
t_token		*peek_tok(t_token *head)
{
	return (curr_tok);
}

t_token		*consume_tok(t_token **head, t_tok_type expected)
{
	//check match
	if (curr_tok != expected)
		return (print syntax error)

	tokens = (*tokens)->next;
	return (tok);

}




