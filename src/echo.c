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

int	ft_echo(char **args)
{
	int	i;
	int	print_n;

	i = 1;
	print_n = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		print_n = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_n)
		printf("\n");
	return (0);
}
