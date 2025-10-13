/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:05:05 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/13 15:07:13 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <lexer.h>
#include <token.h>
#include "libft.h"


static void append_char(t_scanner *scanner, char c)
{
	if (scanner->buff_idx < 1023)
		scanner->buffer[scanner->buff_idx++] = c;
}
//buffer nul terminated
static char *get_buff_lexeme(t_scanner *scanner)
{
	scanner->buffer[scanner->buff_idx] = '\0';
	return (ft_strdup(scanner->buffer));
}
static void advance(t_scanner *scanner)
{
	scanner->pos++;
}
static char peek(t_scanner *scanner)
{
	if (scanner->pos >= scanner->lenght)
		return ('\0');
	return (scanner->input[scanner->pos]);
}
static char peek_next(t_scanner *scanner)
{
	if (scanner->pos + 1 >= scanner->lenght)
		return ('\0');
	return (scanner->input[scanner->pos + 1]);
}
