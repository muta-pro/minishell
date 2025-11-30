/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/11/30 18:50:34 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (0);
	build_env(envp, &env);

	char **testargs;
	testargs = malloc(sizeof(testargs));
	if (!testargs)
		return 1;
	testargs[0] = ft_strdup("ls");
	testargs[1] = ft_strdup("-l");
	testargs[2] = NULL;
	
	t_ast_node simple_cmd = {
    .type = NODE_CMND,
    .left = NULL,
    .right = NULL,
    .args = testargs,
	.redir_list = NULL
	};
	execute_single_cmd(&simple_cmd, env);

	free_env(&env);
	return (0);
}
