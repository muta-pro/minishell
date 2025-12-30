/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 22:15:08 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/30 18:47:07 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_external_print_err(char *cmnd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
	write(STDERR_FILENO, ": ", 2);
	perror("");
}

void	handle_exec_errors(t_shell *shell, t_ast_node *cmd, char *cmnd)
{
	char	**two_d_env;

	if (access(cmnd, F_OK) == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		child_cleanup_exit(shell, 127);
	}
	if (is_dir(cmnd))
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
		write(STDERR_FILENO, ": Is a directory\n", 17);
		child_cleanup_exit(shell, 126);
	}
	two_d_env = list_to_2d(shell->env_list);
	child_sig_handler();
	execve(cmnd, cmd->args, two_d_env);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmnd, ft_strlen(cmnd));
	write(STDERR_FILENO, ": ", 2);
	perror("");
	free_arr(two_d_env);
	child_cleanup_exit(shell, 126);
}

int	is_dir(const char *path)
{
	int		fd;
	int		dir;
	char	buffer;

	dir = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, &buffer, 0) == -1 && errno == EISDIR)
		dir = 1;
	close(fd);
	return (dir);
}
