/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 16:14:30 by joko          #+#    #+#                 */
/*   Updated: 2025/12/29 17:46:36 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parent_request_exit(t_shell *shell, int code)//????
{
	shell->save_exit_status = code;
	shell->should_exit = 1;
	return (-42);
}

static int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_ast_node *cmd, t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (cmd->args[1])
	{
		if (is_num_str(cmd->args[1]) == 0)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, cmd->args[1], ft_strlen(cmd->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (parent_request_exit(shell, 2));
		}
		if (cmd->args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		return (parent_request_exit(shell,
				(unsigned char)ft_atoi(cmd->args[1])));
	}
	else
		return (-42);
}
