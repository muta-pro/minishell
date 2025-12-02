/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:25:30 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/01 18:48:07 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_getcwd()
{
	char	*cwd;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_chdir(t_ast_node *cmd, t_env *env)
{
	char	*rltv_to_full;
	char	*current;

	if (cmd->args[1] == NULL || !(strncmp(cmd->args[1], "~", 1)))
	{
		while (strcmp(env->key, "HOME"))
			env = env->next;
		chdir(env->value);
	}
	else if (!(strncmp(cmd->args[1], "/", 1)))
		chdir(cmd->args[1]);
	else
	{
		current = getcwd(NULL, 0);
		rltv_to_full = ft_strjoin(current, "/");
		free(current);
		current = ft_strdup(rltv_to_full);
		rltv_to_full = ft_strjoin(current, cmd->args[1]);
        free(current);
		if (chdir(rltv_to_full) == -1)
			perror(rltv_to_full);
		free(rltv_to_full);
	}
	ft_getcwd();
}

void	ft_exit(char *exit_status)
{
	if (exit_status)
	{
		printf("exit\n");
		exit(atoi(exit_status));
	}
	else
		exit(0);
}

void	ft_env(t_env *env)
{
	t_env	*node;

	node = env;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}

void	ft_export(t_env **env, char *str)
{
	t_env	*temp;
	t_env	*start;
	int		i;

	i = 0;
	start = *env;
	while ((*env)->next)
		*env = (*env)->next;
	temp = add_new_node();
	(*env)->next = temp;
	while (str[i] != '=')
		i++;
	temp->key = strndup(&str[0], i);
	while (str[i])
		i++;
	temp->value = strndup(&str[strlen(temp->key) + 1], i - (strlen(temp->key) + 1));
	(*env) = start;
}

void	ft_unset(t_env **env, char *str)
{
	t_env	*temp;
	temp = *env;
	while (strcmp((*env)->key, str))
		*env = (*env)->next;
	if (!(*env))
		return ;
	while (temp->next != *env)
		temp = temp->next;
	temp->next = (*env)->next;
	free((*env)->key);
	free((*env)->value);
	free((*env)->next);
	free(*env);
}