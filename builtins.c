/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:25:30 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/06 16:33:01 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getcwd(char *input_line)
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	if (!(strcmp("pwd", input_line)))
		printf("%s\n", cwd);
	free(cwd);
}

void	ft_chdir(char	*input_line, char *abso_path, char *rltv_path)
{
	(void)input_line;
	char	*rltv_to_full;
	char	*current;

	if (abso_path)
		chdir(abso_path);
	else if (rltv_path)
	{
		current = getcwd(NULL, 0);
		rltv_to_full = ft_strjoin(current, "/");
		free(current);
		current = ft_strdup(rltv_to_full);
		rltv_to_full = ft_strjoin(current, rltv_path);
        free(current);
		chdir(rltv_to_full);
        free(rltv_to_full);
	}
}
