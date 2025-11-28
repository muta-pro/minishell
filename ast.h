/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 17:12:21 by yneshev       #+#    #+#                 */
/*   Updated: 2025/11/19 16:24:09 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdlib.h> // For NULL

/*
 * This enum comes from your token.h.
 * The executor needs it to understand what a redirection token means.
*/
typedef enum e_token_type
{
	T_WORD,
	T_STR,
	TGWATEVER, // The executor doesn't care about these...
	// ...
	T_REDIR_IN,      // <
	T_REDIR_OUT,     // >
	T_REDIR_APPEND,  // >>
	T_REDIR_HEREDOC  // <<
	// ...and so on
}	t_token_type;


/*
 * This enum comes from syntax_tree.h.
 * It's the "tag" for a struct.
*/
typedef enum e_node_type
{
	PIPELINE,
	COMMAND,
	ARGUMENT,
	REDIRECTION,
	MERROR
}	t_node_type;


/*
 * This is the "material" (a linked list for args/redirs).
 * From syntax_tree.h.
*/
typedef struct s_options
{
	t_node_type			node_type;
	t_token_type		token_type; // The executor checks this for <, >, >>
	char				*content;   // The argument ("ls") or file ("out.txt")
	struct s_options	*next;
}	t_options;


/*
 * This is the "product" you will pass to your partner.
 * This is the ONLY struct he needs to build his simple-command logic.
 * From syntax_tree.h.
*/
typedef struct s_command
{
	t_node_type	node_type;
	t_options	*arguments;     // List of args (e.g., "ls", "-l")
	t_options	*redirections;  // List of redirs (e.g., ">", "out.txt")
}	t_command;

#endif