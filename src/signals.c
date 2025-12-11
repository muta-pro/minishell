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
Clean up temp files or pipes

Executor Flow 
Your partner's execute_AST function must follow this template:
Call set_parent_signals_exec().
fork()
Child Process: Call set_child_signals(),
 perform redirections, and call execve.
Parent Process: waitpid() for the child to finish, 
then call signal(SIGINT, handle_sigint) to restore the prompt handler.*/
#include "shell.h"
#include <signal.h>

void	install_parent_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	child_sig_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_parent_sig_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_got_sigint = 1;
	// write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	handle_sigint_hrdc(int sig)
{
	(void)sig;
	g_got_sigint = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
