/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:03 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/27 17:01:40 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//LEXICAL ANALYSIS
//TEST :
//cat file | grep word
//echo hello > output.txt

#include "shell.h"

t_token	*create_token(t_tok_type type, const char *lexeme)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (lexeme)
		token->lexeme = ft_strdup(lexeme);
	else
		token->lexeme = NULL;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	insert_token(t_token **head, t_token *new_token)
{
	t_token	*curr;

	if (!new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_token;
	}
}

void	free_tok(t_token *tok)
{
	t_token	*tmp;

	while (tok != NULL)
	{
		tmp = tok->next;
		free(tok->lexeme);
		free(tok);
		tok = tmp;
	}
}
// nospace_oper();
