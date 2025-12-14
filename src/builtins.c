/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:25:30 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/12 21:37:12 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <limits.h>

int	ft_getcwd()
{
	char	*cwd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd:");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_chdir(t_ast_node *cmd, t_shell *shell)
{
	char	*target_path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	printf("cd\n");
	if (getcwd(old_pwd, PATH_MAX) == NULL)
	{
		perror("cd: getcwd error");
		return (1);
	}
	if (cmd->args[1] == NULL || strcmp(cmd->args[1], "~") == 0)
	{
		target_path = get_env_val(shell->env_list, "HOME");
		if (target_path == NULL || *target_path == '\0')
		{
			// fprintf(stderr, "minishell: cd: HOME not set\n"); // change fprintf
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else if (strcmp(cmd->args[1], "-") == 0)
	{
		target_path = get_env_val(shell->env_list, "OLDPWD");
		if (target_path == NULL || *target_path == '\0')
		{
			fprintf(stderr, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", target_path);
	}
	else
		target_path = cmd->args[1];
	// change dir
	if (chdir(target_path) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: ", target_path);
		perror("");
		return (1);
	}
	// update pwds
	set_env_val(&shell->env_list, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, PATH_MAX) != NULL)
		set_env_val(&shell->env_list, "PWD", new_pwd);
	else
	{
		perror("minishell: cd: getcwd error after change");
		return (1);
	}
	return (0);
}

int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_ast_node *cmd, int exit_status)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (cmd->args[1])
	{
		if (is_num_str(cmd->args[1]) == 0)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, cmd->args[1], ft_strlen(cmd->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit(2);
		}
		if (cmd->args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		exit(atoi(cmd->args[1])); // atoll maybe
	}
	else
		exit(exit_status); // fix this with exit code
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
	t_env	*curr;
	t_env	*prev;

	if (env == NULL || *env == NULL || str == NULL)
		return ;
	curr = *env;
	prev = NULL;
	while (curr && strcmp(curr->key, str))
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return ;
	if (prev == NULL)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}
