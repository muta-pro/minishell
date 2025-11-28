/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:59:07 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 14:57:09 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
use signal(SIGINT, child_handler) or 
sigaction immediately after fork() in your Executor code.*/
#include "shell.h"
#include <signal.h>

static void	install_parent_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

child_sig_handler()
heredoc_sig_handler()