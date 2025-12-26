/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 16:16:41 by joko          #+#    #+#                 */
/*   Updated: 2025/12/26 16:21:42 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    update_if_exists(t_env **env, t_xp *xp)
{
    t_env *curr_env = *env;
    while (curr_env)
    {
        if (strcmp(curr_env->key, xp->key) == 0) // ft_
        {
            if (xp->eqptr)
            {
                free(curr_env->value);
                curr_env->value = ft_strdup(xp->eqptr + 1);
                if (!curr_env->value)
                {
                    write(STDERR_FILENO,
                            "minishell: export: cannot allocate memory\n", 42);
                    exit (EXIT_FAILURE);
                }
            }
            xp->key_found = 1;
            break ;
        }
        curr_env = curr_env->next;
    }
}

void    export_new_node(t_env **env, t_xp *xp)
{
    t_env *new_node;

    if (!(xp->key_found))
    {
        new_node = add_new_node();
        new_node->key = ft_strdup(xp->key);
        if (xp->eqptr)
            new_node->value = ft_strdup(xp->eqptr + 1);
        else
            new_node->value = NULL;
        new_node->next = NULL;
        env_add_last(env, new_node);
    }
    free(xp->key);
    xp->i++;
}

int valid_id(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void    print_export(t_env *env)
{
	t_env	*node;

	node = env;
	while (node)
	{
		printf("declare -x %s", node->key);
		if (node->value)
			printf("=%s", node->value);
		printf("\n");
		node = node->next;
	}
}

void    parse_export_arg(t_ast_node *node, t_xp *xp)
{
    xp->curr = node->args[xp->i];
    xp->eqptr = ft_strchr(xp->curr, '=');
    xp->key_found = 0;
    if (xp->eqptr)
        xp->key = strndup(xp->curr, xp->eqptr - xp->curr); // ft_ !!!
    else
        xp->key = ft_strdup(xp->curr);
}