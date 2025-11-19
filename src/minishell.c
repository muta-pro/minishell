/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:15:36 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/19 13:10:25 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "sgnl.h"

volatile sig_atomic_t	g_got_sigint = 0;

// static void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_got_sigint = 1;
// 	write(STDOUT_FILENO, "\n", 1);
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**envp_cpy;
	t_token		*tokens;
	// t_ast		*ast;

	(void)(argc);
	(void)(argv);
	// install_parent_handler();
	envp_cpy = copy_envp(envp);
	init_shlvl(envp_cpy); //to handle mem alloc failure
	while (1)
	{
		if (g_got_sigint)
		{
			g_got_sigint = 0;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		line = readline("minishell: ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = lexer(line); // tokenize
			if (tokens)
				print_tokens(tokens);
			else
				printf("Lexer returned NULL or an error.\n");
			if (!tokens)
			{
				free(line);
				continue ;
			}
			// ast = parser(tokens);
			// if (!ast)
			// {
			// 	free_tok(tokens);
			// 	free(line);
			// 	continue ;
			// }
			// execute(ast, envp_cpy);
			// free_ast(ast);
			free_tok(tokens);
		}
		free(line);
	}
	// clear_history();
	// free_envp(envp_cpy);
	return (0);
}

//	how do I chek if SHLVL exits, then decrement