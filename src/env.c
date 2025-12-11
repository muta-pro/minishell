/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/11 20:26:46 by yneshev       ########   odam.nl         */
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
				return ("");
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	set_env_val(t_env **env, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *env;
	while (curr)
	{
		if(!strcmp(curr->key, key))
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			if (curr->value == NULL)
				return (printf("rip")); // handle malloc failure
		}
		curr = curr->next;
	}

	// If key not found make new node
	new_node = add_new_node();
	if (new_node == NULL)
		return (printf("rip2")); // malloc
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);

	if (new_node->key == NULL || new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (printf("rip3")); // malloc..
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
	int		c;
	t_env	*temp;
	t_env	*start;

	start = *env;
	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		(*env)->key = strndup(envp[i], j);
		// (*env)->key = ft_substr(envp[i], 0, j);
		c = 1;
		while (envp[i][j] && c++)
			j++;
		(*env)->value = strndup(envp[i] + j - c + 2, c - 2);
		// printf("\n\nj - c: %d", j -c);
		// (*env)->value = ft_substr(envp[i], j - c, c);
		if (envp[i + 1])
		{
			temp = add_new_node(); // protect
			(*env)->next = temp;
			*env = temp;
		}
		i++;
	}
	(*env)->next = NULL;
	*env = start;
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
