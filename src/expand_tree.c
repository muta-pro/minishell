/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:07:29 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 15:16:43 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
#include "shell.h"

void expand_ast(t_ast_node *node, char **envp)
{
	if (!IN_QT_STATE && c == '$')
		get_env_var();
}

char *substitute_and_clean(char *str, char **envp, int quotes)
{

}