/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:07:29 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/01 19:10:48 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
$USER is a string - traverse AST, look each arg and replace strings.
*/
#include "parser.h"
#include "shell.h"

void	expand_ast(t_ast_node *node, char **envp)
{
	int		i;
	char	*new_str;

	if (!node)
		return ;
	if (node->type == NODE_CMND && node->args)
	{
		i = 0;
		while (node->args[i])
		{
			if (!IN_QT_STATE && ft_strchr(node->args[i], '$'))
			{
				new_str = expand_str(node->);
			}

		}
	}
}

char	*substitute_and_clean(char *arg, char **envp)
{
	char	*value;
	char	*str;

	if (arg[0] == '\'')
		str = eliminate_qt(arg);
	else if (arg[0] == '"')
	{
		value = repace_key_value(arg, envp);
		str = eliminate_qt(value);
		free(value);
	}
	else
		str = repace_key_value(arg, envp);
	return (str);
}

void	repace_key_value(t_token **curr)
{
	expand_ast(curr, envp);
}

char	*eliminate_qt(char *str)
{
	char	*clean_str;
	int		i;
	size_t	len;

	len = ft_strlen(str);
	clean_str = malloc(sizeof(char) * (len -1));
	if (!clean_str)
	{
		g_exit_status = 1;
		return (NULL);
	}
	i = 1;
	while (i < len - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	return (clean_str);
}
