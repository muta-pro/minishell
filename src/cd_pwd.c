/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joko <joko@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 15:42:34 by joko          #+#    #+#                 */
/*   Updated: 2025/12/26 23:25:47 by joko          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int  ft_chdir(char *target_path)
{
    if (chdir(target_path) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: ", target_path);
		perror("");
		if (target_path)
			free(target_path);
		return (1);
	}
	if (target_path)
		free(target_path);
    return (0);
}

static int  update_pwds(t_shell *shell, char *old_pwd, char *new_pwd)
{
    if (set_env_val(&shell->env_list, "OLDPWD", old_pwd) == 1)
		return (1);
	if (getcwd(new_pwd, PATH_MAX) != NULL)
    {
		if (set_env_val(&shell->env_list, "PWD", new_pwd) == 1)
			return (1);
        return (0);
    }
	else
	{
		perror("minishell: cd: getcwd error after change");
		return (1);
	}
}

static int  parse_cd_args(t_shell *shell, t_ast_node *cmd, char **target_path)
{
    if (cmd->args[1] == NULL || strcmp(cmd->args[1], "~") == 0)
	{
		*target_path = get_env_val(shell->env_list, "HOME");
		if (*target_path == NULL || **target_path == '\0')
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			return (free(*target_path), 1);
		}
	}
	else if (strcmp(cmd->args[1], "-") == 0)
	{
		*target_path = get_env_val(shell->env_list, "OLDPWD");
		if (*target_path == NULL || **target_path == '\0')
		{
			write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
			return (free(*target_path), 1);
		}
		printf("%s\n", *target_path);
	}
	else
		*target_path = ft_strdup(cmd->args[1]);
    return (0);
}

int	ft_getcwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd:");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_cd(t_ast_node *cmd, t_shell *shell)
{
	char	*target_path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

    target_path = NULL;
	if (getcwd(old_pwd, PATH_MAX) == NULL)
	{
		perror("cd: getcwd error");
		return (1);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
    if (parse_cd_args(shell, cmd, &target_path) == 1)
        return (1);
    if (ft_chdir(target_path) == 1)
        return (1);
    if (update_pwds(shell, old_pwd, new_pwd) == 1)
        return (1);
    return (0);
}
