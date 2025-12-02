/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_class.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/29 14:33:29 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:09:43 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// int	get_char_id(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n')
// 		return (C_WS);
// 	if (c == '|')
// 		return (C_P);
// 	if (c == '"' || c == '\'')
// 		return (C_Q);
// 	if (c == '&')
// 		return (C_OP);
// 	if (c == '$')
// 		return (C_V);
// 	if (c == '<' || c == '>')
// 		return (C_R);
// 	if (c == '\0')
// 		return (C_EOF);
// }

// boundaries_id();

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_operator_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

//drops whitespace/tabs/newlines before collecting token
int	valid_char(char c)
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
