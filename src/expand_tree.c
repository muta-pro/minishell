/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tree.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/28 15:07:29 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:18 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_dollar(char *arg, int *i, char **res, t_env *env)
{
	char	*value;

	value = get_var_value(arg, i, env);
	*res = ft_strjoin_free(*res, value);
	free(value);
}

char	*get_var_value(char *str, int *i, t_env *env)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_val(env, var);
	free(var);
	return (value);
}

char	*substitute_and_clean(char *arg, t_env *env)
{
	char	*result;
	int		i;
	int		in_dqt;

	in_dqt = 0;
	result = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_dqt)
			handle_sngl_qt(arg, &i, &result);
		else if (arg[i] == '"')
		{
			in_dqt = !in_dqt;
			i++;
		}
		else if (arg[i] == '$' && (ft_isalnum(arg[i + 1])
				|| arg[i + 1] == '_' || arg[i + 1] == '?'))
			handle_dollar(arg, &i, &result, env);
		else
			result = join_char(result, arg[i++]);
	}
	free(arg);
	return (result);
}

void	expand_ast(t_ast_node *node, t_env *env)
{
	int		i;
	t_redir	*tmp;

	if (!node)
		return ;
	expand_ast(node->left, env);
	expand_ast(node->right, env);
	if (node->type == NODE_CMND)
	{
		i = 0;
		while (node->args && node->args[i])
		{
			node->args[i] = substitute_and_clean(node->args[i], env);
			i++;
		}
		tmp = node->redir_list;
		while (tmp)
		{
			if (tmp->file_name && !tmp->no_expand)
				tmp->file_name = substitute_and_clean(tmp->file_name, env);
			tmp = tmp->next;
		}
	}
}
