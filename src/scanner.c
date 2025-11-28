/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:07:01 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 15:18:51 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

t_token	*scan_word(t_scanner *scanner)
{
	scanner->buff_idx = 0;
	while (!is_whitespace(peek(scanner)) && !is_operator_char(peek(scanner))
		&& peek(scanner) != '\0' && peek(scanner) != '$')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	return (create_token(T_WORD, get_buff_lexeme(scanner)));
}

// static void	scan_token(const char *input_text)
// {
// 	while (**input_text == ' ')
// 		(*input_text)++;
// 	if (**input_text == '\0')
// 		return (t_tok_type);
// 	{T_EOF, NULL};
// }

t_token	*scan_operator(t_scanner *scanner)
{
	char	c;
	char	*lexeme;

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
	if (strcmp(lexeme, "|") == 0)
		return (create_token(T_PIPE, lexeme));
	if (strcmp(lexeme, "<") == 0)
		return (create_token(T_REDIR_IN, lexeme));
	if (strcmp(lexeme, ">") == 0)
		return (create_token(T_REDIR_OUT, lexeme));
	if (strcmp(lexeme, "<<") == 0)
		return (create_token(T_REDIR_HEREDOC, lexeme));
	if (strcmp(lexeme, ">>") == 0)
		return (create_token(T_REDIR_APPEND, lexeme));
	if (strcmp(lexeme, "||") == 0)
		return (create_token(T_LOGIC_OR, lexeme));
	if (strcmp(lexeme, "&&") == 0)
		return (create_token(T_LOGIC_AND, lexeme));
	free(lexeme);
	return (create_token(T_ERROR, "Unknown operator"));
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
		return (create_token(T_EXIT_STATUS, get_buff_lexeme(scanner)));
	}
	if (is_whitespace(peek(scanner)) || is_operator_char(peek(scanner))
		|| peek(scanner) == '\0')
		return (create_token(T_WORD, get_buff_lexeme(scanner)));
	while (ft_isalnum(peek(scanner)) || peek(scanner) == '_')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	return (create_token(T_VAR, get_buff_lexeme(scanner)));
}

t_token	*scan_quoted_str(t_scanner *scanner)
{
	char	quote_type;

	scanner->buff_idx = 0;
	quote_type = peek(scanner);
	append_char(scanner, peek(scanner));
	advance(scanner);
	while (peek(scanner) != quote_type && peek(scanner) != '\0')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	if (peek(scanner) == '\0')
		return (create_token(T_ERROR, "Unclosed quote"));
	append_char(scanner, peek(scanner));
	advance(scanner);
	return (create_token(T_STR, get_buff_lexeme(scanner)));
}
