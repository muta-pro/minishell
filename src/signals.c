/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 19:59:07 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:51 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
use signal(SIGINT, child_handler) or 
sigaction immediately after fork() in your Executor code.
for chile process before running a command
child process receives SIGINT
Catch SIGINT during heredoc input
Exit heredoc early without crashing
Clean up temp files or pipes*/
#include "shell.h"
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_got_sigint = 1;
}

// static void eof_exit(char *line)
// {
// 	if (!line)
// 		return (NULL);
// 	write(1, "Exit", 4);
// 	break ;
// }

// static void	install_parent_handler(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(EOF, handle_exit);
// }

// static void child_sig_handler(int sig)
// {
// 	void(sig);
// 	g_got_sigint = 1;
// 	write(STDOUT_FILENO, "\n", 1);
// }
// static void heredoc_sig_handler()