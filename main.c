/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/02 20:39:41 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char *input_line;

	while (1)
	{
		input_line = readline("minishell> ");
		if (input_line == NULL)
		{
			printf("\nExiting.\n");
			break;
		}
		if (input_line && *input_line)
		{
			add_history(input_line);
			printf("You entered: %s\n", input_line);
		}
		free(input_line);
		input_line = NULL;
	}
	return (0);
}
