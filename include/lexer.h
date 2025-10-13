/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:50:31 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/13 17:40:34 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

typedef struct s_env
{
	char	**envp;
	int		count;
	int		capacity;
}	t_env;

//curr state of the scanner
typedef struct s_scanner
{
	const char		*input;
	int				pos;
	int				lenght;
	t_scan_state	state;
	t_token			*head;
	char			buffer[1024]; //g_lexeme_buff
	int				buff_idx; //g_buff_indx
}	t_scanner;

typedef struct s_ast
{

}	t_ast;

t_token	*lexer(char *input_text);
t_token	*scan_next_tok(t_scanner *scanner);
t_token	*scan_word(t_scanner *scanner);
t_token	*scan_operator(t_scanner *scanner);
void	init_scanner(t_scanner *scanner, char *input_text);

#endif