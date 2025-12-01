/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/01 22:12:05 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "shell.h"

// t_ast_node *create_command_node(char **args);
// void free_ast2(t_ast_node *node);
// t_ast_node *test_ls_simple();
// t_ast_node *test_pipe_simple();

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env	*env;

// 	env = (t_env *)malloc(sizeof(*env));
// 	if (!env)
// 		return (0);
// 	build_env(envp, &env);

// 	// char **testargs;
// 	// testargs = malloc(sizeof(testargs));
// 	// if (!testargs)
// 	// 	return 1;
// 	// testargs[0] = ft_strdup("ls");
// 	// testargs[1] = ft_strdup("-l");
// 	// testargs[2] = NULL;
	
// 	// t_ast_node simple_cmd = {
//     // .type = NODE_CMND,
//     // .left = NULL,
//     // .right = NULL,
//     // .args = testargs,
// 	// .redir_list = NULL
// 	// };
// 	// execute_single_cmd(&simple_cmd, env);

// 	t_ast_node *test_node = test_pipe_simple();
//     // t_ast_node *test_node = test_ls_simple();
// 	execute_AST(env, test_node);
// 	free_ast2(test_node);
// 	free_env(&env);
// 	return (0);
// }
