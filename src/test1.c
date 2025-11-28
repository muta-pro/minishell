/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:25:46 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 20:15:59 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"


// Helper to get string names for token types
const char	*token_type_to_string(t_tok_type type)
{
    switch (type)
    {
        case T_WORD: return "WORD";
        case T_STR: return "STRING";
        case T_VAR: return "VAR";
        case T_PIPE: return "PIPE";
        case T_REDIR_IN: return "<";
        case T_REDIR_OUT: return ">";
        case T_REDIR_APPEND: return ">>";
        case T_REDIR_HEREDOC: return "<<";
        case T_LOGIC_OR: return "OR";
        case T_LOGIC_AND: return "AND";
        case T_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

void	print_tokens(t_token *tokens)
{
    printf("\n=== 1. LEXER OUTPUT (Tokens) ===\n");
        while (tokens)
        {
            printf("[%s] -> %s\n", token_type_to_string(tokens->type), tokens->lexeme);
            tokens = tokens->next;
        }
        printf("================================\n");
}

void print_ast(t_ast_node *node, int level)
{
    if (!node) return;

    // Indentation for tree depth
    for (int i = 0; i < level; i++) printf("    ");

    if (node->type == NODE_PIPE)
        printf("\033[1;31m[PIPE]\033[0m\n");
    else if (node->type == NODE_AND)
        printf("\033[1;33m[AND]\033[0m\n");
    else if (node->type == NODE_OR)
        printf("\033[1;33m[OR]\033[0m\n");
    else if (node->type == NODE_CMND)
    {
        printf("\033[1;32m[CMD]\033[0m ");
        
        // Print Args
        if (node->args)
        {
            for (int i = 0; node->args[i]; i++)
                printf("'%s' ", node->args[i]);
        }
        
        // Print Redirections attached to this command
        t_redir *r = node->redir_list;
        while (r)
        {
            printf("\033[0;36m(Redir: %d -> %s)\033[0m ", r->type, r->file_name);
            r = r->next;
        }
        printf("\n");
    }

    // Recursively print children
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

int main(int argc, char **argv)
{
    char *input;
    
        if (argc > 1)
            input = argv[1];
        else
            input = "ls -la | grep .c && echo 'Build Success' || echo 'Build Fail'";
    
        printf("Input: \"%s\"\n", input);
    
        // 1. Run Lexer
        t_token *tokens = lexer(input);
        if (!tokens)
        {
            printf("Error: Lexer returned NULL\n");
            return (1);
        }
        print_tokens(tokens);
    
        // 2. Run Parser
        // parser() takes the head of the token list
        t_ast_node *ast = parser(tokens);
        
        printf("\n=== 2. PARSER OUTPUT (AST) ===\n");
        if (!ast)
            printf("Error: Parser returned NULL (Syntax Error)\n");
        else
            print_ast(ast, 0);
        printf("==============================\n");
    
        // 3. Cleanup
        // Note: In your real shell, you free AST after execution. 
        // Since we aren't executing, we free it here.
        if (ast) 
            free_ast(ast, NULL); 
        
        // Note: Your parser might consume tokens, or your free_ast might not free 
        // the tokens themselves depending on implementation. 
        // Usually, you free tokens separately if they aren't linked into the AST.
        // For this test, we can let OS cleanup or call free_tok(tokens);
        
        return (0);

    
}