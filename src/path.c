/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 18:32:38 by yneshev       #+#    #+#                 */
/*   Updated: 2025/11/30 18:33:01 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

char	*get_path(char **twoDenv, char *cmd)
{
	int		i = 0;
	char	*paths;
	char	**split_paths;
	char	*full_path;

	paths = NULL;
	while (twoDenv && twoDenv[i])
	{
		if (!(strncmp("PATH=", twoDenv[i], 5)))
		{
			paths = ft_strdup(twoDenv[i] + 5);
			if (!paths)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, ':');
	free(paths);
	full_path = find_path(split_paths, cmd);
	if (!full_path)
		return (free_arr(split_paths), NULL);
	return (free_arr(split_paths), full_path);
}
