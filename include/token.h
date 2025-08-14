/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:38:12 by imutavdz          #+#    #+#             */
/*   Updated: 2025/08/05 18:31:25 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKENS_H
# define TOKENS_H

typedef enum token_type
{
	T_EOF,
	T_IDENTIF,
	T_STR,
	T_PIPE,
	T_SEMICO,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_BACKGR,
	T_WORD,
	T_FLAG,
	T_DELIMITER,
	T_EXIT_STATUS,
	T_ERROR
}	tt;

typedef struct s_token
{
	tt		type;
	char	*lexeme;
	struct	s_token *next;
}			t_token;

void init_lex();
t_token new_token();
t_token lex_next_tok();
void free_tok(t_token *tok);

#endif