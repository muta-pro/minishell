/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:46:11 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/17 19:04:32 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
1 definistions MACRO

2 rules REGULAR-EXPRESSION + C CODE 

3 C code ALL THE REST

WHAT'S THE NEXT TOKEN?
*/
#include "lexer.h"
#include "token.h"
#include "libft.h"

get_next_char();// manage the state of the lexer
//append char to scanner's buffer

//single character tokens | ; < > & (>>)
//words are identifires and flags starting with -
//handle quotes and single quotes backticks
//all else is an error TOKEN
void	init_scanner(t_scanner *scanner, char *input_text)
{
	scanner.input = input_text;
	scanner.pos = 0;
	scanner.lenght = ft_strlen(input_text);
	scanner.head = NULL;
	scanner.state = IN_DEADULT;
}

t_token	*lexer(char *input_text)
{
	t_scanner	scanner;
	t_token		*token;

	scanner_init(scanner);
	if (!input_text)
		return (NULL);
	while (1)
	{
		token = scan_next_tok(&scanner);
		if (token == NULL && scanner->pos >= scanner.lenght)
		{
			insert_token(&scanner.head, create_token(T_EOF, NULL));
			break ;
		}
		if (token == NULL || token->type == T_ERROR)
		{
			free_tok(scanner.head);
			if (token)
				free(token);
			return (NULL);
		}
		insert_token(&scanner.head, token);
	}
	return (scanner.head);
}

 //define categories of tokens/should split using space delimiter.
tokenizing()
{
	if (inv_token())
		return (error);
}

t_token	*scan_next_tok(t_scanner *scanner)
{
	char	c;

	c = peek(scanner);
	while (is_whitespace(scanner->input[scanner->pos]))
		scanner->pos++;
	if (scanner->pos >= scanner->lenght)
		return (NULL);
	if (is_quote(c))
		return (quoted_str_scan(scanner));
	else if (is_operator(c))
		return (operator_scan(scanner));
	else if (c == '$')
		return (var_scan(scanner));
	else if (c == '$' && peek_next(scanner) == '?')
		return (exit_status_scan(scanner));
	else
		return (scan_word(scanner));
}
