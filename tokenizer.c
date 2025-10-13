/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:03 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/13 17:40:46 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//LEXICAL ANALYSIS
//TEST :
//cat file | grep word
//echo hello > output.txt

#include <stdlib.h>
#include <stdio.h>
#include "token.h"

t_token	create_token(const char *value, t_tok_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexeme = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}
void insert_token(t_token **head, t_token *new_token)
{
	t_token *curr;

	if (!new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		curr = *head;
		while (curr->next ! NULL)
			curr = curr->next;
	}
	curr->next = new_token;
}

nospace_oper();
free_tok();
operators();
is_redirection();