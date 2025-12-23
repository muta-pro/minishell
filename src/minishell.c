/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 16:15:36 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/21 20:13:51 by imutavdz       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cleanup_pack(char *line, t_token *tok, t_ast_node *ast)
{
	if (ast)
	{
		clean_tmp(ast);
		free_ast(ast);
	}
	if (tok)
		free_tok(tok);
	if (line)
		free(line);
}

t_ast_node	*build_ast(char *line, t_token **tok, t_shell *shell)
{
	t_ast_node	*ast;

	*tok = lexer(line);
	if (!*tok)
		return (NULL);
	ast = parser(*tok, shell);
	if (!ast)
		return (NULL);
	return (ast);
}

int	run_ast(t_ast_node *ast, t_shell *shell)
{
	int	h_count;

	h_count = 0;
	here_docs(ast, &h_count, shell);
	if (g_got_sigint)
		return (shell->exit_status);
	expand_ast(ast, shell);
	execute_ast(shell, ast);
	return (shell->exit_status);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	char		*line;
// 	t_token		*tokens;
// 	t_ast_node	*ast;
// 	int			h_count;
// 	t_shell		shell;

// 	(void)(argc);
// 	(void)(argv);
// 	shell.exit_status = 0;
// 	shell.env_list = NULL;
// 	build_env(envp, &shell.env_list);
// 	install_parent_handler();
// 	init_shlvl(&shell); //to handle mem alloc failure
// 	while (1)
// 	{
// 		g_got_sigint = 0;
// 		line = readline("minishell: ");
// 		if (g_got_sigint)
// 		{
// 			shell.exit_status = 130;
// 			if (line)
// 				free(line);
// 			continue ;
// 		}
// 		if (!line)
// 		{
// 			write(STDOUT_FILENO, "exit\n", 6);
// 			free_env(&shell.env_list);
// 			exit(shell.exit_status);
// 		}
// 		if (!*line)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		tokens = lexer(line);
// 		if (tokens)
// 			ast = parser(tokens);
// 		else
// 			ast = NULL; //lexer failed
// 		if (ast)
// 		{
// 			h_count = 0;
// 			here_docs(ast, &h_count, &shell);
// 			if (g_got_sigint)
// 			{
// 				clean_tmp(ast);
// 				free_on_err(line, tokens, ast);
// 				continue ;
// 			}
// 			expand_ast(ast, &shell);
// 			execute_ast(&shell, ast);
// 			debug_ast(ast, 0);
// 			clean_tmp(ast);
// 			free_ast(ast);
// 		}
// 		else if (tokens) //parser failure
// 			shell.exit_status = 258;
// 		if (tokens)
// 			free_tok(tokens);
// 		free(line);
// 	}
// 	// clear_history();
// 	free_env(&shell.env_list);
// 	return (0);
// }
