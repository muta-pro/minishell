/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/04 12:30:54 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:38 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
implement recursive descent parser approach
Start the main parsing routine, checking for the highest precedence first
parse_cmnd : scans until hits pipe, op or EOF;
have args arr to hold words
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
	t_ast_node	*pipe_nd;

	left = parse_cmnd(tokens);
	if (!left)
		return (NULL);
	while (peek_tok(*tokens) && peek_tok(*tokens)->type == T_PIPE)
	{
		consume_tok(tokens, T_PIPE);
		pipe_nd = create_ast_nd(NODE_PIPE, NULL, NULL);
		if (!pipe_nd)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_nd->left = left;
		pipe_nd->right = parse_pipeline(tokens);
		if (!pipe_nd->right)
		{
			free_ast(pipe_nd);
			return (NULL);
			print_shell_err(SYTX_ERR, "No command.");
		}
		left = pipe_nd;
	}
	return (left);
}

t_ast_node	*parse_cmnd(t_token **tokens)
{
	t_ast_node	*node;
	char		**args;
	t_redir		*redirs;
	int			flag;

	redirs = NULL;
	args = NULL;
	flag = 0;
	while (!is_delim(peek_tok(*tokens)))
	{
		flag = args_redirs_tok(tokens, &args, &redirs);
		if (flag != 0)
		{
			print_shell_err(SYTX_ERR, "Unexpected token.");
			free_arr(args);
			free_redirs(redirs);
			return (NULL);
		}
	}
	if (!args && !redirs)
		return (NULL);
	node = create_ast_nd(NODE_CMND, NULL, NULL);
	node->args = args;
	node->redir_list = redirs;
	return (node);
}

int	parse_redir(t_token **tokens, t_redir **redir_head)
{
	t_redir	*new_node;
	t_token	*op;
	t_token	*file;

	op = consume_tok(tokens, peek_tok(*tokens)->type);
	file = consume_tok(tokens, T_WORD);
	if (!file)
		file = consume_tok(tokens, T_STR);
	if (!file)
		file = consume_tok(tokens, T_VAR);
	if (!file)
		file = consume_tok(tokens, T_EXIT_STATUS);
	if (!file)
		return (1);
	new_node = init_redir_node(op, file);
	if (!new_node)
		return (1);
	redir_add_node(redir_head, new_node);
	return (0);
}
//malloc and init new ast_nd
