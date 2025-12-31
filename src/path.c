/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:32:38 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 22:19:00 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*find_path(char **split_paths, char *cmd)
{
	int		i;
	char	*current_path;
	char	*temp;

	if (!split_paths)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		temp = ft_strjoin(split_paths[i], "/");
		current_path = ft_strjoin(temp, cmd);
		free(temp);
		if (current_path && access(current_path, F_OK | X_OK) == 0)
			return (current_path);
		free(current_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **two_d_env, char *cmd)
{
	t_path_vars	pv;

	pv.i = 0;
	pv.paths = NULL;
	while (two_d_env && two_d_env[pv.i])
	{
		if (!(ft_strncmp("PATH=", two_d_env[pv.i], 5)))
		{
			pv.paths = ft_strdup(two_d_env[pv.i] + 5);
			if (!pv.paths)
				return (NULL);
			break ;
		}
		pv.i++;
	}
	if (!pv.paths)
		return (NULL);
	pv.split_paths = ft_split(pv.paths, ':');
	free(pv.paths);
	pv.full_path = find_path(pv.split_paths, cmd);
	if (!pv.full_path)
		return (free_arr(pv.split_paths), NULL);
	return (free_arr(pv.split_paths), pv.full_path);
}
