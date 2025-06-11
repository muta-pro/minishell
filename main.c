/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/06 19:55:08 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			add_history(input_line);
		ft_getcwd(input_line);
		if (!(strcmp("cd test", input_line)))
			ft_chdir(NULL, "test");
		free(input_line);
		input_line = NULL;
	}
	return (0);
}