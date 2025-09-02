/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:38:12 by imutavdz          #+#    #+#             */
/*   Updated: 2025/09/01 15:49:38 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENS_H
# define TOKENS_H

# include "lexer.h"


typedef enum token_type
{
	T_EOF,
	T_IDENTIF,
	T_VAR,
	T_HEREDOC,
	T_STR,
	T_PIPE,
	T_SEMICOL,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_BCKGRND,
	T_WORD,
	T_LOGIC_AND,
	T_LOGIC_OR,
	T_DELIMITER,
	T_EXPAND_HERDOC,
	T_NON_EXPAND_HERDOC,
	T_EXPAND_HERDOC_DELIM,
	T_NON_EXPAND_HERDOC_DELIM,
	T_EXIT_STATUS,
	T_ERROR
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*lexeme;
	struct	s_token	*next;
}					t_token;

int is_strT(t_token *tok);
int is_varT(t_token *tok);
int is_pipeT(t_token *tok);
int is_quoteT(t_token *tok);
int is_redirT(t_token *tok);
int is_delimT(t_token *tok);
int is_exitstatusT(t_token *tok);
int is_appendableT(t_token *tok);

t_tok_type	get_toktype(t_state state);
void init_lex();
t_token new_token();
t_token lex_next_tok();
void free_tok(t_token *tok);

#endif