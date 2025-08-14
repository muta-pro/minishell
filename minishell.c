/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:15:36 by imutavdz          #+#    #+#             */
/*   Updated: 2025/08/04 23:20:57 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*readline(const char *prompt);

void	handle_sig(int sig)
{
	(void)sig;
	write(1, "\nminishell: ", 12);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		token;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (*line && line)
			add_history(line);
		printf("%s\n", line);
		token = lexer(line);
		printf("%s\n", token);
		// parse(token);
		free (line);
		line = NULL;	
	}
	clear_history();
	return (0);
}
