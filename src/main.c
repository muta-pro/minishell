/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/01 21:36:36 by imutavdz      ########   odam.nl         */
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
	ast = NULL;
	ast = build_ast(line, &tokens, shell);
	shell->curr_tok = tokens;
	shell->curr_ast = ast;
	if (!ast)
	{
		cleanup_pack(NULL, tokens, NULL);
		shell->curr_tok = NULL;
		return (shell->exit_status);
	}
	status = run_ast(ast, shell);
	cleanup_pack(NULL, tokens, ast);
	shell->curr_tok = NULL;
	shell->curr_ast = NULL;
	return (status);
}

static void	handle_sigint_status(t_shell *shell)
{
	if (g_got_sigint)
	{
		shell->exit_status = 130;
		g_got_sigint = 0;
	}
}

char	*read_input(t_shell *shell)
{
	(void)shell;
	g_got_sigint = 0;
	return (readline("minishell: "));
}

int	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_input(shell);
		if (!line)
			break ;
		handle_sigint_status(shell);
		if (*line)
			add_history(line);
		shell->exit_status = run_line(line, shell);
		free(line);
		if (shell->exit_status == -42 || shell->should_exit)
			return (shell->save_exit_status);
	}
	return (shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	if (argv == NULL || argv[0] == NULL || argv[0][0] == '\0')
		return (0);
	ft_bzero(&shell, sizeof(t_shell));
	build_env(envp, &shell.env_list);
	shell.exit_status = 0;
	install_parent_handler();
	shell.exit_status = shell_loop(&shell);
	rl_clear_history();
	free_env(&shell.env_list);
	return (shell.exit_status);
}
