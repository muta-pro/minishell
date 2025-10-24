/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:25:46 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/21 16:27:31 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"

// Helper to get string names for token types
const char	*token_type_to_string(t_tok_type type)
{
    switch (type)
    {
        case T_WORD: return "T_WORD";
        case T_STR: return "T_STR";
        case T_VAR: return "T_VAR";
        case T_PIPE: return "T_PIPE";
        case T_LESS: return "T_LESS";
        case T_GREAT: return "T_GREAT";
        case T_DLESS: return "T_DLESS";
        case T_DGREAT: return "T_DGREAT";
        case T_EXIT_STATUS: return "T_EXIT_STATUS";
        case T_EOF: return "T_EOF";
        case T_ERROR: return "T_ERROR";
        default: return "T_UNKNOWN";
    }
}

void	print_tokens(t_token *tokens)
{
    t_token	*current;
    
    printf("---- TOKEN LIST ----\n");
    current = tokens;
    while (current != NULL)
    {
        printf("Type: %-15s Lexeme: [%s]\n",
               token_type_to_string(current->type),
               current->lexeme ? current->lexeme : "NULL");
        current = current->next;
    }
    printf("--------------------\n");
}
