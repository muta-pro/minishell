/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:38:12 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/16 16:03:23 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKEN_H
# define TOKEN_H

typedef enum token_type
{
	T_DELIMITER, //special char marking end of token [space/tab/newline]
	T_WORD, //word
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
	T_ERROR,
	T_LPAREN,
	T_RPAREN,
	T_WILDC,
	T_ENV,
	T_SNGL_Q,
	T_DBL_Q,
	T_MIX_Q
}	t_tok_type;

typedef enum e_scan_state //state management for the lexer
{
	IN_DEFAULT,
	IN_SNGL_QUOTE,
	IN_DBL_QUOTE,
	IN_ESCAPE,
	IN_STRING,
	IN_HEREDOC,
	IN_VAR,
	IN_PIPE,
	IN_LOGICAL
}	t_scan_state;

typedef struct s_token
{
	t_tok_type		type;
	char			*lexeme;
	t_scan_state	state;
	struct	s_token	*next;
}					t_token;


//token list management
t_token			*create_token(t_tok_type type, const char *lexeme);
void			insert_token(t_token **head, t_token *new_token);
void			free_tok(t_token *tok);
t_tok_type		get_op_type(char *lexeme);
// void			remove_nxt_tok(t_token *token);
// int 			add_tok_to_list(t_token **list, t_scan_state state, char *buf);
//it can directly use the t_scan_state to determine the token type to create
//FOR THE PARSER check for token type
// int				is_string_token(t_token *token);
// int				is_variable_token(t_token *token);
// int				is_pipe_token(t_token *token);
// int				is_delimiter_token(t_token *token);
// int				is_exit_status_token(t_token *token);
// int				is_redir_token(t_token *token);
// int				is_quote_token(t_token *token);
// int				is_concat_token(t_token *token);
#endif