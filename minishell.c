/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:15:36 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/18 20:04:44 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_nl();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**envp_cpy;
	t_token		*tokens;
	t_ast		*ast;

	(void)(argc);
	(void)(argv);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	envp_cpy = copy_envp(envp);
	init_shlvl(&envp_cpy); //to handle mem alloc failure
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokens = lexer(line);//tokenize
			if (!tokens)
			{
				free(line);
				continue ;
			}
			ast = parser(tokens);
			if (!ast)
			{
				free_tok(tokens);
				free(line);
				continue ;
			}
			execute(ast, envp_cpy);
			free_ast(ast);
			free_tok(tokens);
		}
		free(line);
	}
	clear_history();
	free_envp(envp_cpy);
	return (0);
}

//	how do I chek if SHLVL exits, then decrement