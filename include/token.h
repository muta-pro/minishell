/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:38:12 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/20 18:34:17 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENS_H
# define TOKENS_H

typedef enum scan_state //state management for the lexer
{
	IN_DEFAULT,
	IN_SNGL_QUOTE,
	IN_DBL_QUOTE,
	IN_ESCAPE
} t_scan_state;


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
	T_LPAREN,
	T_RPAREN,
	T_EOF,
	T_ERROR
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
int	is_redirection(char c);
int	valid_char (char c);
int	null_terminator(char c);

t_scan_state	sngl_quote(char **buff, char curr, size_t *i);
t_scan_state	dbl_quote(char **buff, char curr, size_t *i);

//token list management
t_token		*create_token(t_tok_type type, const char *lexeme);
void		insert_tokrn(t_token **head, t_token *new_token);
void		free_tok(t_token *tok);

#endif