/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:19:29 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/30 19:53:37 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
process_token to determine if is redir/ arg / garbage
skip unknown tokens to pervent inf loops on garbage
*/
#include "shell.h"
#include <stddef.h>

static void	args_redirs_tok(t_token **tokens, char ***args, t_redir **redirs)
{
	t_token	*curr;

	curr = peek_tok(*tokens);
	if (is_redir_token(curr))
		parse_redir(tokens, redirs);
	else if (peek_tok(*tokens)->type == T_WORD
		|| peek_tok(*tokens)->type == T_STR
		|| peek_tok(*tokens)->type == T_VAR)
	{
		append_args(args, curr->lexeme);
		consume_tok(tokens, curr->type);
	}
	else
		consume_tok(tokens, curr->type);
}

static t_tok_type	get_op_type(char *lexeme)
{
	if (!strcmp(lexeme, "|"))
		return (T_PIPE);
	if (!strcmp(lexeme, "<"))
		return (T_REDIR_IN);
	if (!strcmp(lexeme, ">"))
		return (T_REDIR_OUT);
	if (strcmp(lexeme, "<<"))
		return (T_REDIR_HEREDOC);
	if (strcmp(lexeme, ">>"))
		return (T_REDIR_APPEND);
	if (strcmp(lexeme, "||"))
		return (T_LOGIC_OR);
	if (strcmp(lexeme, "&&"))
		return (T_LOGIC_AND);
	return (T_ERROR);
}

// int	is_pipe_token(t_token *token)
// {
// 	if (token != NULL && token->type == T_PIPE)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int	is_delimiter_token(t_token *token)
// {
// 	if (token != NULL && token->type == T_DELIMITER)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int	is_string_token(t_token *token)
// {
// 	if (token != NULL && token->type == T_STR)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int	is_exit_status_token(t_token *token)
// {
// 	if (token != NULL && token->type == T_EXIT_STATUS)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int	is_variable_token(t_token *token)
// {
// 	if (token != NULL && token->type == T_VAR)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }
