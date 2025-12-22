/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/01 21:36:36 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_got_sigint = 0;

int	run_line(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_ast_node	*ast;
	int			status;

	tokens = NULL;
	ast = build_ast(line, &tokens, shell);
	if (!ast)
	{
		if (tokens)
			shell->exit_status = 258;
		cleanup_pack(NULL, tokens, NULL);
		return (shell->exit_status);
	}
	status = run_ast(ast, shell);
	cleanup_pack(NULL, tokens, ast);
	return (status);
}

char	*read_input(t_shell *shell)
{
	char	*line;

	(void)shell;
	g_got_sigint = 0;
	line = readline("minishell: ");
	if (g_got_sigint == SIGINT)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

int	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		g_got_sigint = 0;
		line = read_input(shell);
		if (g_got_sigint == SIGINT)
		{
			shell->exit_status = 130;
			continue ;
		}
		if (!line)
			break ;
		if (*line)
			add_history(line);
		shell->exit_status = run_line(line, shell);
		free(line);
	}
	return (shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		status;

	(void)argc;
	if (argv == NULL || argv[0] == NULL || argv[0][0] == '\0')
		return (0);
	ft_bzero(&shell, sizeof(t_shell));
	build_env(envp, &shell.env_list);
	shell.exit_status = 0;
	install_parent_handler();
	status = shell_loop(&shell);
	write(STDOUT_FILENO, "exit\n", 5);
	rl_clear_history();
	free_env(&shell.env_list);
	return (shell.exit_status);
}
