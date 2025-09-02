/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:50:31 by imutavdz          #+#    #+#             */
/*   Updated: 2025/08/29 13:23:06 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

typedef enum scan_state
{
	IN_STRING,
	IN_HEREDOC,
	IN_DEFAULT,
	IN_SNGL_QUOTE,
	IN_DBL_QUOTE,
	IN_ESCAPE
} t_scan_state;

#endif