/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_unset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 15:00:50 by joko          #+#    #+#                 */
/*   Updated: 2025/12/26 16:25:00 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_add_last(t_env **env, t_env *new_node)
{
	t_env	*curr;

	curr = *env;

	if (env == NULL || new_node == NULL)
		return ;
	if (*env == NULL)
		*env = new_node;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}

int	ft_export(t_env **env, t_ast_node *node)
{
	t_xp	xp;

	xp.i = 1;
	xp.exit_status = 0;
	if (node->args[1] == NULL)
		return (print_export(*env), 0);
	while (node->args[xp.i])
	{
        parse_export_arg(node, &xp);
		if (!valid_id(xp.key))
		{
            write(STDERR_FILENO, "minishell: export: '", 20);
            write(STDERR_FILENO, xp.curr, ft_strlen(xp.curr));
            write(STDERR_FILENO, "': not a valid identifier\n", 26);
            free(xp.key);
			xp.exit_status = 1;
			xp.i++;
			continue ;
		}
        update_if_exists(env, &xp);
        export_new_node(env, &xp);
	}
	return (xp.exit_status);
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
