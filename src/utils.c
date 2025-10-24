/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:05:05 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/22 09:59:53 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <lexer.h>
#include <token.h>
#include "libft.h"

void	append_char(t_scanner *scanner, char c)
{
	if (scanner->buff_idx < 1023)
		scanner->buffer[scanner->buff_idx++] = c;
}

//buffer nul terminated
char	*get_buff_lexeme(t_scanner *scanner)
{
	scanner->buffer[scanner->buff_idx] = '\0';
	return (ft_strdup(scanner->buffer));
}

void	advance(t_scanner *scanner)
{
	scanner->pos++;
}

char	peek(t_scanner *scanner)
{
	if (scanner->pos >= scanner->lenght)
		return ('\0');
	return (scanner->input[scanner->pos]);
}

char	peek_next(t_scanner *scanner)
{
	if (scanner->pos + 1 >= scanner->lenght)
		return ('\0');
	return (scanner->input[scanner->pos + 1]);
}

// boundaries_id();

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_operator_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '$' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
//drops whitespace/tabs/newlines before collecting token
void	invalid_tok();

int	valid_char	(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	null_terminator(char c)
{
	if (c == '\0')
		return (1);
	return (0);
}

t_scan_state	*curr_state(char *input_text)
{
	t_scan_state state;
	if (input_text == 39)
		state = IN_SNGL_QUOTE;
	if (input_text == 34)
		state = IN_DBL_QUOTE;
	if (input_text == 92)
		state = IN_ESCAPE;
	else
		state = IN_DEAFULT;
	return (state);
}
