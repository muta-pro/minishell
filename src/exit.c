/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 16:14:30 by joko          #+#    #+#                 */
/*   Updated: 2025/12/29 16:57:29 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int  is_num_str(char *str)
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
			exit(2);
		}
		if (cmd->args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			// shell->exit_status = 1;
			// return (-42);
		}
		shell->exit_status = atoi(cmd->args[1]);
		return (-42);
	}
	else
		return (-42);
}