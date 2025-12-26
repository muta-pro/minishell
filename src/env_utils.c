/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:25:30 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 16:29:45 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**list_to_2d(t_env *env)
{
	char	**env_array;
	char	*temp;
	int		i;

	env_array = malloc((list_size(env) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		env_array[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*get_env_val(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (env->value == NULL)
				return (NULL);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
