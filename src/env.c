/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/29 17:09:04 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	set_val_new_node(t_env **node, const char *key, const char *value)
{
	*node = add_new_node();
	if (node == NULL)
		return ((write(STDERR_FILENO,
					"minishell: fatal error: cannot allocate memory\n",
					47)), 1);
	(*node)->key = ft_strdup(key);
	(*node)->value = ft_strdup(value);
	if ((*node)->key == NULL || (*node)->value == NULL)
	{
		free((*node)->key);
		free((*node)->value);
		free((*node));
		return (write(STDERR_FILENO,
				"minishell: fatal error: cannot allocate memory\n", 47), 1);
	}
	return (0);
}

static int	find_key(t_env **curr, const char *key, const char *value)
{
	while (*curr)
	{
		if (!ft_strcmp((*curr)->key, key))
		{
			free((*curr)->value);
			(*curr)->value = ft_strdup(value);
			if ((*curr)->value == NULL)
				return (write(STDERR_FILENO,
						"minishell: fatal error: cannot allocate memory\n",
						47), 1);
			return (0);
		}
		*curr = (*curr)->next;
	}
	return (2);
}

int	set_env_val(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	t_env	*new_node;
	int		rtrn;

	curr = *env;
	new_node = NULL;
	rtrn = find_key(&curr, key, value);
	if (rtrn != 2)
		return (rtrn);
	if (set_val_new_node(&new_node, key, value) == 1)
		return (1);
	if (*env == NULL)
		*env = new_node;
	else
	{
		curr = *env;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_node;
	}
	return (0);
}

void	build_env(char **envp, t_env **env)
{
	t_build_env	be;

	*env = NULL;
	be.i = 0;
	while (envp[be.i])
	{
		be.node = add_new_node();
		if (!be.node)
			return ;
		be.j = 0;
		while (envp[be.i][be.j] != '=')
			be.j++;
		be.node->key = strndup(envp[be.i], be.j);
		be.node->value = ft_strdup(envp[be.i] + be.j + 1);
		if (*env == NULL)
			*env = be.node;
		else
		{
			be.last = *env;
			while (be.last->next)
				be.last = be.last->next;
			be.last->next = be.node;
		}
		be.i++;
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
