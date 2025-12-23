/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/11 10:42:05 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:09:32 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
append_args - add str to char **array;
resizing array to add + 1 new item + 1 '\0' for execve
we copy pointers - move reference - to the new arr;
clead old arr but string is where the new list points.
if first arg, allocate space for it + '\0'
copy  it and mark end of arr
update pointer of args to point to the new array
*/
#include "shell.h"

t_ast_node	*create_ast_nd(t_node_t type, t_ast_node *l, t_ast_node *r)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);//should error handle return null
	node->type = type;
	node->left = l;
	node->right = r;
	node->args = NULL;
	node->redir_list = NULL;
	return (node);
}

void	append_args(char ***args, char *new_arg)
{
	int		count;
	char	**new_list;
	int		i;

	count = 0;
	if (*args)
	{
		while ((*args)[count])
			count++;
		new_list = malloc(sizeof(char *) * (count + 2));
		i = 0;
		while (i < count)
		{
			new_list[i] = (*args)[i];
			i++;
		}
		free(*args);
	}
	else
		new_list = malloc(sizeof(char *) * 2);
	if (!new_list)
		return ;
	new_list[count] = strdup(new_arg);
	new_list[count + 1] = NULL;
	*args = new_list;
}
