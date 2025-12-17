/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scanner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:07:01 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:48 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
scan_word : handles quote concatenation / quote removal
iterates chars
FLAG : state var
*/
#include "shell.h"

t_token	*return_string(t_scanner *scanner, t_tok_type type)
{
	t_token	*tok;
	char	*lexeme;

	lexeme = get_buff_lexeme(scanner);
	if (!lexeme)
		return (create_token(T_ERROR, "Malloc fail."));
	tok = create_token(type, lexeme);
	free(lexeme);
	return (tok);
}
//shoul I hanlde here T_STR token and other states??
t_token	*scan_word(t_scanner *scanner)
{
	char			c;
	t_scan_state	state;

	state = IN_DEFAULT;
	scanner->buff_idx = 0;
	c = peek(scanner);
	while (c != '\0')
	{
		if (chop_word(state, c))
			break ;
		if (handle_qt_switch(&state, scanner, c))
		{
			c = peek(scanner);
			continue ;
		}
		append_char(scanner, c);
		advance(scanner);
		c = peek(scanner);
	}
	if (state == IN_SNGL_QUOTE || state == IN_DBL_QUOTE)
		return (create_token(T_ERROR, "Unclosed quote."));
	return (return_string(scanner, T_WORD));
}

t_token	*scan_operator(t_scanner *scanner)
{
	char			c;
	char			*lexeme;
	t_tok_type		type;
	t_token			*tok;

	scanner->buff_idx = 0;
	c = peek(scanner);
	append_char(scanner, c);
	advance(scanner);
	if ((c == '<' && peek(scanner) == '<')
		|| (c == '>' && peek(scanner) == '>')
		|| (c == '|' && peek(scanner) == '|')
		|| (c == '&' && peek(scanner) == '&'))
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	lexeme = get_buff_lexeme(scanner);
	type = get_op_type(lexeme);
	if (type == T_ERROR)
		tok = create_token(T_ERROR, "Unknown operator");
	else
		tok = create_token(type, lexeme);
	free(lexeme);
	return (tok);
}

t_token	*scan_var(t_scanner *scanner)
{
	scanner->buff_idx = 0;
	append_char(scanner, peek(scanner)); //append $
	advance(scanner);
	if (peek(scanner) == '?')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
		return (return_string(scanner, T_EXIT_STATUS));
	}
	if (is_whitespace(peek(scanner)) || is_operator_char(peek(scanner))
		|| peek(scanner) == '\0')
		return (return_string(scanner, T_VAR));
	while (ft_isalnum(peek(scanner)) || peek(scanner) == '_')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	return (return_string(scanner, T_VAR));
}
//Do I need this  T_STR token - ???

// t_token	*scan_quoted_str(t_scanner *scanner)
// {
// 	char	quote_type;

// 	scanner->buff_idx = 0;
// 	quote_type = peek(scanner);
// 	append_char(scanner, peek(scanner));
// 	advance(scanner);
// 	while (peek(scanner) != quote_type && peek(scanner) != '\0')
// 	{
// 		append_char(scanner, peek(scanner));
// 		advance(scanner);
// 	}
// 	if (peek(scanner) == '\0')
// 		return (create_token(T_ERROR, "Unclosed quote"));
// 	append_char(scanner, peek(scanner));
// 	advance(scanner);
// 	return (create_token(T_STR, get_buff_lexeme(scanner)));
// }
