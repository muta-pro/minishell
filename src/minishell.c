/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 16:15:36 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/07 16:55:23 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_got_sigint = 0;
int						g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;
	t_env		*env;
	int			h_count;

	(void)(argc);
	(void)(argv);
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	build_env(envp, &env);
	install_parent_handler();
	// init_shlvl(env); //to handle mem alloc failure
	while (1)
	{
		g_got_sigint = 0;
		line = readline("minishell: ");
		if (g_got_sigint)
		{
			g_exit_status = 130;
			if (line)
				free(line);
			continue ;
		}
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_env(&env);
			exit(g_exit_status);
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = lexer(line);
		if (tokens)
			ast = parser(tokens);
		else
			ast = NULL; //lexer failed
		if (ast)
		{
			h_count = 0;
			here_docs(ast, &h_count);
			if (g_got_sigint)
			{
				clean_tmp(ast);
				free_ast(ast);
				free_tok(tokens);
				free(line);
				continue ;
			}
			expand_ast(ast, env);
			execute_AST(env, ast);
			debug_ast(ast, 0);
			clean_tmp(ast);
			free_ast(ast);
		}
		else if (tokens)//parser failed, not lexer, should print its err
			g_exit_status = 258;
		if (tokens)
			free_tok(tokens);
		free(line);
	}
	// clear_history();
	free_env(&env);
	return (0);
}

//	how do I chek if SHLVL exits, then decrement