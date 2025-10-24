/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:07:01 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/22 09:48:28 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHELL_H
# define SHELL_H
/*Heredoc handling is complex and involves multiple phases:

Tokenizer: recognize <<
Parser: identify the delimiter
Executor: read lines until delimiter
Expander: expand variables if delimiter wasn't quoted*/
# include <stdio.h>

typedef struct s_heredoc
{
	char *delimiter;
	int expand;
}	t_heredoc;

//FOR THE PARSER check for token type
int is_wordT(t_token *tok);
int is_varT(t_token *tok);
int is_pipeT(t_token *tok);
int is_logig_opT(t_token *tok);
int is_redirT(t_token *tok);

#endif