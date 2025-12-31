/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/04 22:19:29 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:11:03 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
process_token to determine if is redir/ arg / garbage
skip unknown tokens to pervent inf loops on garbage
^^^Any token reaching this point that isn't an operator or argument 
(like T_ERROR or T_DELIMITER) should probably be handled by returning 
 an error code from parse_cmnd, not consumed silently.
 can return flag instead of consuming
*/
#include "shell.h"
#include <stddef.h>

int	is_redir_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_APPEND || token->type == T_REDIR_HEREDOC);
}

int	args_redirs_tok(t_token **tokens, char ***args, t_redir **redirs)
{
	t_token	*curr;

	curr = peek_tok(*tokens);
	if (!curr)
		return (0);
	if (is_redir_token(curr))
		return (parse_redir(tokens, redirs));
	else if (peek_tok(*tokens)->type == T_WORD
		|| peek_tok(*tokens)->type == T_VAR
		|| peek_tok(*tokens)->type == T_EXIT_STATUS)
		// || peek_tok(*tokens)->type == T_WILDC)
	{
		append_args(args, curr->lexeme);
		consume_tok(tokens, curr->type);
		return (0);
	}
	else
		return (1);
}

t_tok_type	get_op_type(char *lexeme)
{
	if (!strcmp(lexeme, "|"))
		return (T_PIPE);
	if (!strcmp(lexeme, "<"))
		return (T_REDIR_IN);
	if (!strcmp(lexeme, ">"))
		return (T_REDIR_OUT);
	if (!strcmp(lexeme, "<<"))
		return (T_REDIR_HEREDOC);
	if (!strcmp(lexeme, ">>"))
		return (T_REDIR_APPEND);
	// if (!strcmp(lexeme, "||"))
	// 	return (T_LOGIC_OR);
	// if (!strcmp(lexeme, "&&"))
	// 	return (T_LOGIC_AND);
	// if (!strcmp(lexeme, "*"))
	// 	return (T_WILDC);
	return (T_ERROR);
}

t_tok_type get_other_type(char *lexeme);

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
