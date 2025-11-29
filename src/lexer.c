/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:46:11 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/29 16:26:15 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
define categories of tokens/should split using space delimiter.
get_next_char();// manage the state of the lexer
//append char to scanner's buffer

//single character tokens | ; < > & (>>)
//words are identifires and flags starting with -
//handle quotes and single quotes backticks
//add a  condition statements for determing if change of state
//all else is an error TOKEN
//MISSING LOGIC FOR TOKENIZATION && ||

WHAT'S THE NEXT TOKEN?
*/
#include "shell.h"

void	init_scanner(t_scanner *scanner, char *input_text)
{
	scanner->input = input_text;
	scanner->pos = 0;
	scanner->lenght = ft_strlen(input_text);
	scanner->head = NULL;
	scanner->state = IN_DEFAULT;
	scanner->buff_idx = 0;
}

t_token	*lexer(char *input_text)
{
	t_scanner	scanner;
	t_token		*token;

	init_scanner(&scanner, input_text);
	if (!input_text)
		return (NULL);
	while (1)
	{
		token = scan_next_tok(&scanner);
		if (token == NULL)
		{
			insert_token(&scanner.head, create_token(T_EOF, NULL));
			break ;
		}
		if (token->type == T_ERROR)
		{
			//print error message from token->lexeme
			free_tok(scanner.head);
			free_tok(token);
			return (NULL);
		}
		insert_token(&scanner.head, token);
	}
	return (scanner.head);
}

t_token	*scan_next_tok(t_scanner *scanner)
{
	char	c;

	while (is_whitespace(peek(scanner)))
		advance(scanner);
	c = peek(scanner);
	if (c == '\0')
		return (NULL);
	if (c == '\'' || c == '"')
		return (scan_quoted_str(scanner));
	else if (is_operator_char(c))
		return (scan_operator(scanner));
	else if (c == '$')
		return (scan_var(scanner));
	else
		return (scan_word(scanner));
}

t_scan_state	switch_state(t_scan_state curr, char c)
{
	if (curr == IN_SNGL_QUOTE && c == '\'')
		return (IN_DEFAULT);
	if (curr == IN_DBL_QUOTE && c == '"')
		return (IN_DEFAULT);
	if (curr == IN_ESCAPE)
		return (IN_DEFAULT);
	if (curr == IN_DEFAULT)
	{
		if (c == '\\')
			return (IN_ESCAPE);
		if (c == '\'')
			return (IN_SNGL_QUOTE);
		if (c == '"')
			return (IN_DBL_QUOTE);
	}
	return (curr);
}
