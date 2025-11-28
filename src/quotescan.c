/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotescan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:59:33 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 20:01:55 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//handle single quote
//handle doubble quote
//inside/ouside quotes
//quote state
#include "shell.h"

t_scan_state	sngl_quote(t_scanner *scanner)
{
	append_char(scanner, '\'');
	return (IN_SNGL_QUOTE);
}

t_scan_state	dbl_quote(t_scanner *scanner)
{
	append_char(scanner, '"');
	return (IN_DBL_QUOTE);
}
