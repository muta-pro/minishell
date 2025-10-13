/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:38:12 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/11 14:23:19 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENS_H
# define TOKENS_H

# include "lexer.h"

typedef enum token_type
{
	T_WORD, //word
	T_STR, //quoted str
	T_EXIT_STATUS, //$?
	T_VAR, //$HOME
	T_PIPE, //|
	T_LOGIC_OR, //||
	T_LOGIC_AND, //&&
	T_REDIR_IN, //<
	T_REDIR_OUT, //>
	T_REDIR_APPEND, //>>
	T_REDIR_HEREDOC, //<<
	T_EOF,
	T_ERROR
	T_LPAREN;
	T_RPAREN;
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*lexeme;
	struct	s_token	*next;
}					t_token;
//check characters
int is_operator_char(char c);
int is_whitespace(char c);
int is_quote(char c);
int is_spec_char(char c);

t_tok_type	get_toktype(t_state state);
void init_lex();
t_token *create_token(t_tok_type type, char *lexeme);
t_token *insert_tokrn(t_token **head, t_token *new_token);
t_token lex_next_tok();
void free_tok(t_token *tok);

#endif