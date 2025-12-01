/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 17:54:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/11/30 18:23:59 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		// printf("\n\nj - c: %d", j -c);                                              !!!!!!
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

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
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

char	*new_env_str(char *key, char *value)
{
	char	*result;
	int		len;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_strcpy(result, key);
	ft_strcat(result, "=");
	ft_strcat(result, value);
	return (result);
}

int	update_env_var(char ***envp, char *key, char *value)
{
	char	*new_var;
	int		i;

	new_var = new_env_str(key, value);
	if (!new_var)
		return ;
	i = find_env_varible(key, value);
	if (i >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = new_var;
	}
	else
		add_env_var(envp, new_var);
}

char	**copy_envp(char **envp);//dup env

char	*get_env_value(char **envp, char *key);//read var value

void	unset_env_var(char ***envp, char *key);//remove var
void	**free_envp(char **envp);//cleanup

