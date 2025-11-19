/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:28:22 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/19 16:06:18 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
recursive node structure that can represent either an operator or a command.
Define the type of node in the AST
A structure to hold information about a single redirection.
core AST node structure. It is recursive:
	- The command and its arguments (argv-style array).
	- All redirections for this command.
*/
#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "libft.h"

typedef enum e_node_type
{
	NODE_CMND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_t;

typedef struct s_redir
{
	t_tok_type		type;
	char			*file_name;
	struct s_redir	*next;	
}					t_redir;

typedef struct s_ast_node
{
	t_node_t			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				**args;
	t_redir				*redir_list;

}	t_ast_node;

//main parser entry point
t_ast_node	*paser(t_token *token);

t_ast_node	*parse_logic_op(t_token *token_list);
t_ast_node	*parse_pipilne(t_token **tokens);
t_ast_node	*parse_cmnd(t_token **tokens);
t_redir *parse_redir(t_token **tokens);

t_token		*peek_tok(t_token *head);
t_token		*consume_tok(t_token **head, t_tok_type expected);
void		append_arg(char ***args, char *new_arg);
int			is_redir_tok(t_token *token);

#endif