/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:19:29 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 14:57:18 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include <stddef.h>

int	is_pipe_token(t_token *token)
{
	if (token != NULL && token->type == T_PIPE)
	{
		return (1);
	}
	return (0);
}

int	is_delimiter_token(t_token *token)
{
	if (token != NULL && token->type == T_DELIMITER)
	{
		return (1);
	}
	return (0);
}

int	is_string_token(t_token *token)
{
	if (token != NULL && token->type == T_STR)
	{
		return (1);
	}
	return (0);
}

int	is_exit_status_token(t_token *token)
{
	if (token != NULL && token->type == T_EXIT_STATUS)
	{
		return (1);
	}
	return (0);
}

int	is_variable_token(t_token *token)
{
	if (token != NULL && token->type == T_VAR)
	{
		return (1);
	}
	return (0);
}
