/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:25:30 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/24 18:24:32 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getcwd(t_cmd	*cmd)
{
	(void)cmd;
	char	*cwd;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_chdir(t_cmd *cmd)
{
	char	*rltv_to_full;
	char	*current;

	if (!(strncmp(cmd->full_cmd[0], "cd /", 4)))
		chdir(cmd->full_cmd[0] + 3);	
	else
	{
		current = getcwd(NULL, 0);
		rltv_to_full = ft_strjoin(current, "/");
		free(current);
		current = ft_strdup(rltv_to_full);
		rltv_to_full = ft_strjoin(current, cmd->full_cmd[0] + 3);
        free(current);
		if (chdir(rltv_to_full) == -1)
			perror(rltv_to_full);
		free(rltv_to_full);
	}
}

void	ft_exit(char *exit_status)
{
	if (exit_status)
	{
		printf("exit\n");
		exit(atoi(exit_status));

	}
	else
		exit(0);
}