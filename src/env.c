/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/26 16:29:34 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


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

void	ft_env(t_env *env)
{
	t_env	*node;

	node = env;
	while (node)
	{
		if (node->value != NULL)
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
