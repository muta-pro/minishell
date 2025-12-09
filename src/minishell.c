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

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_got_sigint = 1;
}


int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;
	t_env		*env;
	int 		h_count;

	(void)(argc);
	(void)(argv);
	(void)(envp);
	env = malloc(sizeof(env));
	if (!env)
		return (0);
	build_env(envp, &env);
	// install_parent_handler();
	// init_shlvl(env); //to handle mem alloc failure
	// signal(SIGINT, handle_sigint);
	// signal(SIQUIT, SIG_ING);
	while (1)
	{
		g_got_sigint = 0;
		line = readline("minishell: ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = lexer(line); // tokenize
		if (tokens)
			ast = parser(tokens);
		else
			ast = NULL; //lexer failed
		if (ast)
		{
			debug_ast(ast, 0);
			h_count = 0;
			// here_docs(ast, &h_count);
			if (g_got_sigint)
			{
				free_ast(ast);
				continue ;
			}
			printf("T_REDIR_APPEND: %d\nnode type: %d\n", T_REDIR_APPEND, ast->redir_list->type);
			// expand_ast(ast, env);
			execute_AST(env, ast);
			free_ast(ast);
		}
		else if (tokens)
			print_shell_err(SYTX_ERR, "ast failed", 258);
		if (tokens)
			free_tok(tokens);
		free(line);
	}
	// clear_history();
	// free_envp(envp_cpy);
	return (0);
}

//	how do I chek if SHLVL exits, then decrement