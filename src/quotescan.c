/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotescan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:59:33 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/29 16:52:02 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//handle single quote
//handle doubble quote
//inside/ouside quotes
//quote state
#include "shell.h"

// t_scan_state	sngl_quote(t_scanner *scanner)
// {
// 	append_char(scanner, '\'');
// 	return (IN_SNGL_QUOTE);
// }

// t_scan_state	dbl_quote(t_scanner *scanner)
// {
// 	append_char(scanner, '"');
// 	return (IN_DBL_QUOTE);
// }

static int	chop_word(t_scan_state state, char c)
{
	if (state != IN_DEFAULT)
		return (0);
	if (is_whitespace(c) || is_operator_char(c) || c == '$')
		return (1);
	return (0);
}

static int	handle_qt_switch(t_scan_state *state, t_scanner *scanner, char c)
{
	if (state == IN_DEFAULT && (c == '\'' || c == '"'))
	{
		if (c == '\'')
			*state = IN_SNGL_QUOTE;
		else
			*state = IN_DBL_QUOTE;
		append_char(scanner, c);
		advance(scanner);
		return (1);
	}
	else if (state == IN_SNGL_QUOTE && c == '\'')
	{
		*state = IN_DEFAULT;
		append_char(scanner, c);
		advance(scanner);
		return (1);
	}
	else if (state == IN_DBL_QUOTE && c == '"')
	{
		*state = IN_DEFAULT;
		append_char(scanner, c);
		advance(scanner);
		return (1);
	}
	return (0);
}
