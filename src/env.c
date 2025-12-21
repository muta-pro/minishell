/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/21 19:05:33 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_env_val(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (env->value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (NULL);
}

void	set_env_val(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *env;
	while (curr)
	{
		if (!strcmp(curr->key, key))
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			if (curr->value == NULL)
				(printf("rip")); // handle malloc failure
			return ;
		}
		curr = curr->next;
	}
	// If key not found make new node
	new_node = add_new_node();
	if (new_node == NULL)
		(printf("rip2")); // malloc
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (new_node->key == NULL || new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		(printf("rip3")); // malloc..
	}
	if (*env == NULL)
	{
		*env = new_node;
	}
	else
	{
		curr = *env;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_node;
	}
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
