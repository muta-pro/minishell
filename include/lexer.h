/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:50:31 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 20:01:58 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

#include "token.h"

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


t_token	*lexer(char *input_text);
t_token	*scan_next_tok(t_scanner *scanner);
t_token	*scan_word(t_scanner *scanner);
t_token *scan_var(t_scanner *scanner);
t_token	*scan_operator(t_scanner *scanner);
t_token *scan_quoted_str(t_scanner *scanner);
void	init_scanner(t_scanner *scanner, char *input_text);

t_scan_state	sngl_quote(t_scanner *scanner);
t_scan_state	dbl_quote(t_scanner *scanner);

void	append_char(t_scanner *scanner, char c);
char	*get_buff_lexeme(t_scanner *scanner);
void	advance(t_scanner *scanner);
char	peek(t_scanner *scanner);
char	peek_next(t_scanner *scanner);


#endif