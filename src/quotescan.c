/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotescan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:59:33 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/30 16:14:44 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
quote state : scan word runs until whitespace or operator in default
or runs pass it if quote state
*/
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
	if (is_whitespace(c))
		return (1);
	if (is_operator_char(c))
		return (1);
	return (0);
}

static int	handle_qt_switch(t_scan_state *state, t_scanner *scanner, char c)
{
	if (*state == IN_DEFAULT)
	{
		if (c == '\'')
			*state = IN_SNGL_QUOTE;
		else if (c == '"')
			*state = IN_DBL_QUOTE;
		else
			return (0);
		advance(scanner);
		return (1);
	}
	else if (*state == IN_SNGL_QUOTE && c == '\''
		|| *state == IN_DBL_QUOTE && c == '"')
	{
		*state = IN_DEFAULT;
		advance(scanner);
		return (1);
	}
	return (0);
}
