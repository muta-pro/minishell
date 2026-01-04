/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 16:25:27 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/26 16:25:44 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int	is_n(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
