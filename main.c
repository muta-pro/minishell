/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/24 18:29:09 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(t_cmd *cmd)
{
	if (!(strncmp(cmd->full_cmd[0], "cd", 2)))
	{
		ft_chdir(cmd);
	}
	if (!(strcmp(cmd->full_cmd[0], "pwd")))
		ft_getcwd(cmd);
	if (!(strncmp("exit", cmd->full_cmd[0], 4)))
	{
		ft_exit(cmd->full_cmd[0] + 5);
	}
}

int	main(void)
{
	char 	*input_line;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->next = NULL;
	while (cmd)
	{
		input_line = readline("minishell> ");
		cmd->input_line = input_line;
		cmd->full_cmd = &input_line;
		if (input_line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else
			execute_line(cmd);	
		free(input_line);
		input_line = NULL;
	}
	return (0);
}
