/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotescan.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/11 09:59:33 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:10:44 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
quote state : scan word runs until whitespace or operator in default
or runs pass it if quote state
*/
#include "shell.h"

void	handle_sngl_qt(char *arg, int *i, char **res)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '\'')
	{
		*res = join_char(*res, arg[*i]);
		(*i)++;
	}
	if (arg[*i] == '\'')
		(*i)++;
}

int	delim_has_qt(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	chop_word(t_scan_state state, char c)
{
	if (state != IN_DEFAULT)
		return (0);
	if (is_whitespace(c))
		return (1);
	if (is_operator_char(c))
		return (1);
	return (0);
}

int	handle_qt_switch(t_scan_state *state, t_scanner *scanner, char c)
{
	if (*state == IN_DEFAULT)
	{
		if (c == '\'')
			*state = IN_SNGL_QUOTE;
		else if (c == '"')
			*state = IN_DBL_QUOTE;
		else
			return (0);
		append_char(scanner, c);
		advance(scanner);
		return (1);
	}
	else if ((*state == IN_SNGL_QUOTE && c == '\'')
		|| (*state == IN_DBL_QUOTE && c == '"'))
	{
		*state = IN_DEFAULT;
		append_char(scanner, c);
		advance(scanner);
		return (1);
	}
	return (0);
}

char	*eliminate_qt(char *str)
{
	char	*clean_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	clean_str = malloc(sizeof(char) * (len - 1));
	if (!clean_str)
	{
		g_exit_status = 1;
		return (NULL);
	}
	i = 1;
	while (i < len - 1)
	{
		clean_str[i] = str[i];
		i++;
	}
	free(str);
	return (clean_str);
}
