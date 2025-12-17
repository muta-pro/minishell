/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/20 13:28:22 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/12 17:18:43 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
recursive node structure that can represent either an operator or a command.
Define the type of node in the AST
A structure to hold information about a single redirection.
core AST node structure. It is recursive:
	- The command and its arguments (argv-style array).
	- All redirections for this command.
no_expand - 1 for quotes 0 for literal
*/
#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "token.h"

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
	int				no_expand;//flag
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
t_ast_node	*parser(t_token *token);
t_ast_node	*parse_logic_op(t_token **token_list);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_cmnd(t_token **tokens);
int			parse_redir(t_token **tokens, t_redir **redir_head);

t_ast_node	*create_ast_nd(t_node_t type, t_ast_node *l, t_ast_node *r);
void		free_ast(t_ast_node *node);
void		free_arr(char **args);
void		free_redirs(t_redir *redirs);
int			free_on_err(char *line, t_token *tokens, t_ast_node *ast);

t_token		*peek_tok(t_token *head);
t_token		*consume_tok(t_token **head, t_tok_type expected);
void		append_args(char ***args, char *new_arg);
int			is_redir_token(t_token *token);
int			args_redirs_tok(t_token **tokens, char ***args, t_redir **redirs);
int			is_delim(t_token *tok);

t_redir		*init_redir_node(t_token *op, t_token *file);
void		redir_add_node(t_redir **head, t_redir *new_node);

#endif