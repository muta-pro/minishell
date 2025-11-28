/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotescan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:59:33 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 16:32:08 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//handle single quote
//handle doubble quote
//inside/ouside quotes
//quote state
#include "shell.h"

t_scan_state	sngl_quote(char **buff, char curr, size_t *i)
{
	t_scan_state	state;

	state = IN_SNGL_QUOTE;
	if (append_char(buff, curr) == EMALLOC)
		return (ERROR);
	*i += 1;
	return (state);
}

t_scan_state	dbl_quote(char **buff, char curr, size_t *i)
{
	t_scan_state	state;

	state = IN_DBL_QUOTE;
	if (append_char(buff, curr) == EMALLOC)
		return (ERROR);
	*i += 1;
	return (state);
}
