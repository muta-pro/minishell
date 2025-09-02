/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:46:11 by imutavdz          #+#    #+#             */
/*   Updated: 2025/08/17 01:24:21 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
1 definistions MACRO

2 rules REGULAR-EXPRESSION + C CODE 

3 C code ALL THE REST

WHAT'S THE NEXT TOKEN?
*/
#include "lexer.h"
#include "libft.h"

static int	g_curr_char; //EOF
static char	g_lexeme_buff[1024];
static int	g_buff_index;

char	*chop_commandline(const char *delim, char *input)
{
	static char	*mark = NULL;

	if (input != NULL)
		mark = input;
	if (mark == NULL || *mark == '\0')
		return (NULL);
	while (*mark && ft_strchr(delim, *mark) != '\0')
		mark++;
	return (mark);
}

get_next_char();

append_char();

whitespace();//drops whitespace/tabs/newlines before collecting token

switch(g_curr_char); //single character tokens | ; < > & (>>)
//words are identifires and flags starting with -
//handle quotes and single quotes backticks
//all else is an error TOKEN
char	lexemes;

{

}

tt scanner(const char *input_text)
{
	while (**input_text == ' ')
		(*input_text)++;
	if (**input_text == '\0')
		return (tt)
	{T_EOF, NULL};
}

tt lexer(char *input_text)
{
	while (whitespace(g_curr_char))
		to_next_char();
	int	lexeme = scanner(input_text)
	{
		while (input_text)
		{
			if (regex == input_text)
				return (TOKEN_NAME);
		}
	}
	int		value = evaluator(compute numeric values);
	char	token = produce_token(lexeme, value);
	return (token)
} //define categories of tokens/should split using space delimiter.
tokenizing()
{
	if (inv_token())
		return (error);
}

void	parser(char *token)
{
	t_token *tok;

	init_lex();
	tok = next_token();
	pars_tok(tok)
	free_tok(&tok);

}