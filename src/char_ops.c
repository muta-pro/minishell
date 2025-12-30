/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_ops.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/29 14:40:04 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:09:50 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
