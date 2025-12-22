/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tree.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/28 15:07:29 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:18 by imutavdz       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_var_value(char *str, int *i, t_shell *shell)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_val(shell->env_list, var);
	if (!value)
		return (ft_strdup(""));
	free(var);
	return (value);
}

void	handle_dollar(char *arg, int *i, char **res, t_shell *shell)
{
	char	*value;

	value = get_var_value(arg, i, shell);
	*res = ft_strjoin_free(*res, value);
	free(value);
}

void	expand_h_line(char **line, int no_expand, t_shell *shell)
{
	char	*var_line;

	if (no_expand || !*line)
		return ;
	var_line = expand_h_var(*line, shell);
	free(*line);
	*line = var_line;
}

char	*substitute_and_clean(char *arg, t_shell *shell)
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
			handle_dollar(arg, &i, &result, shell);
		else
			result = join_char(result, arg[i++]);
	}
	free(arg);
	return (result);
}

void	expand_ast(t_ast_node *node, t_shell *shell)
{
	int		i;
	t_redir	*tmp;

	if (!node)
		return ;
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
	if (node->type == NODE_CMND)
	{
		i = 0;
		while (node->args && node->args[i])
		{
			node->args[i] = substitute_and_clean(node->args[i], shell);
			i++;
		}
		tmp = node->redir_list;
		while (tmp)
		{
			if (tmp->file_name && !tmp->no_expand)
				tmp->file_name = substitute_and_clean(tmp->file_name, shell);
			tmp = tmp->next;
		}
	}
}
