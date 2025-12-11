/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/01 18:48:11 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_env_val(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

void	build_env(char **envp, t_env **env)
{
	int		i;
	int		j;
	t_env	*node;
	t_env	*last;

	*env = NULL;
	i = 0;
	while (envp[i])
	{
		node = add_new_node();
		if (!node)
			return ;
		j = 0;
		while (envp[i][j] != '=')
			j++;
		node->key = strndup(envp[i], j);
		node->value = strdup(envp[i] + j + 1);
		if (*env == NULL)
			*env = node;
		else
		{
			last = *env;
			while (last->next)
				last = last->next;
			last->next = node;
		}
		i++;
	}
}

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

t_env	*add_new_node(void)
{
	t_env	*new;

	new = malloc(sizeof(new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
