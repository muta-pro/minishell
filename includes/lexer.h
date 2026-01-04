/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:50:31 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/04 19:18:28 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

#include "token.h"

typedef struct s_shell t_shell;

typedef struct s_scanner
{
	const char		*input;
	int				pos; //indx char scan
	int				lenght;
	t_scan_state	state;
	t_token			*head;
	char			buffer[1024]; //g_lexeme_buff
	int				buff_idx; //g_buff_indx
}	t_scanner;

void			init_scanner(t_scanner *scanner, char *input_text);
t_token			*lexer(char *input_text, t_shell *shell);
t_token			*scan_next_tok(t_scanner *scanner);
t_token			*scan_word(t_scanner *scanner);
t_token 		*scan_var(t_scanner *scanner);
t_token			*scan_operator(t_scanner *scanner);
t_token 		*scan_quoted_str(t_scanner *scanner);
t_token			*return_string(t_scanner *scanner, t_tok_type type);

int				chop_word(t_scan_state state, char c);
int				handle_qt_switch(t_scan_state *state, t_scanner *scanner, char c);
t_scan_state	switch_state(t_scan_state curr, char c);
char			*eliminate_qt(char *str);
void			append_char(t_scanner *scanner, char c);
char			*get_buff_lexeme(t_scanner *scanner);
void			advance(t_scanner *scanner);
char			peek(t_scanner *scanner);
char			peek_next(t_scanner *scanner);

#endif