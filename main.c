/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/10/10 15:58:03 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_execve(t_env *env, char **cmd);

void	execute_line(t_cmd *cmd, t_env *env)
{
	__pid_t	pid;


	if (!(strncmp(cmd->full_cmd[0], "cd", 2)))
		ft_chdir(cmd);
	else if (!(strcmp(cmd->full_cmd[0], "pwd")))
		ft_getcwd(cmd);
	else if (!(strncmp("exit", cmd->full_cmd[0], 4)))
		ft_exit(cmd->full_cmd[1]);
	else if (!(strncmp("env", cmd->full_cmd[0], 3)))
		ft_env(env);
	else if (!(strncmp("export", cmd->full_cmd[0], 6)))
		ft_export(&env, cmd->full_cmd[1]);
	else if (!(strncmp("unset", cmd->full_cmd[0], 5)))
		ft_unset(&env, cmd->full_cmd[1]);
	else //(!(strncmp(cmd->full_cmd[0], "ls", 2)))
	{
		pid = fork();
		if (!pid)
		{
			test_execve(env, cmd->full_cmd);
		}
		else
		{
			if (waitpid(pid, NULL, 0) == -1)
				perror("error");
		}
	}
}

t_env	*add_new_node(void)
{
	t_env	*new;

	new = malloc(sizeof(new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	build_env(char **envp, t_env **env)
{
	int		i;
	int		j;
	int		c;
	t_env	*temp;
	t_env	*start;

	start = *env;
	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		(*env)->key = strndup(envp[i], j);
		// (*env)->key = ft_substr(envp[i], 0, j);
		c = 1;
		while (envp[i][j] && c++)
			j++;
		(*env)->value = strndup(envp[i] + j - c + 2, c - 2);
		// printf("\n\nj - c: %d", j -c);                                              !!!!!!
		// (*env)->value = ft_substr(envp[i], j - c, c);
		if (envp[i + 1])
		{
			temp = add_new_node(); // protect
			(*env)->next = temp;
			*env = temp;
		}
		i++;
	}
	*env = start;
}

void free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	while (*cmd)
	{
		temp = *cmd;
		free(temp->full_cmd);
		free(temp->input_line);
		free(temp);
		*cmd = (*cmd)->next;
	}
}

void free_env(t_env **env)
{
	t_env	*temp;
	while (*env)
	{
		temp = *env;
		free(temp->key);
		free(temp->value);
		free(temp);
		*env = (*env)->next;
	}
}

int	list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**list_to_2d(t_env *env)
{
	char	**env_array;
	char	*temp;
	int		i;

	env_array = malloc((list_size(env) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	// env_array = NULL;
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		env_array[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	return (env_array);
}

char	*get_path(char **twoDenv, char *cmd)
{
	int		i = 0;
	char	*paths;
	char	**split_paths;
	char	*current_path;
	while (twoDenv[i])
	{
		if (!(strncmp("PATH=", twoDenv[i], 5)))
			paths = ft_strdup(twoDenv[i] + 5);
		i++;
	}
	split_paths = ft_split(paths, ':');
	free(paths);
	i = 0;
	while (split_paths[i])
	{
		current_path = ft_strjoin(split_paths[i], "/");
		current_path = ft_strjoin(current_path, cmd);
		if (access(current_path, F_OK | X_OK) == 0)
			return (free(split_paths), current_path);
		i++;
	}
	return (NULL);
}

void	test_execve(t_env *env, char **cmd)
{
	char	**twoDenv;
	char	*path;

	path = NULL;
	twoDenv = list_to_2d(env);
	path = get_path(twoDenv, cmd[0]);
	if (execve(path, cmd, twoDenv) == -1)
	{
		exit(0); // handle exit
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char 	*input_line;
	char	**cmnd;
	t_cmd	*cmd;
	t_env	*env;

	cmnd = malloc(sizeof(cmd));
	cmnd[0] = ft_strdup("ls");
	cmnd[1] = ft_strdup("-l");
	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (0);
	build_env(envp, &env);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->next = NULL;
	// test_execve(env, cmnd);
	while (cmd)
	{
		input_line = readline("minishell> ");
		cmd->input_line = input_line;
		// cmd->full_cmd = &input_line;
		cmd->full_cmd = ft_split(input_line, ' ');
		if (input_line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else
			execute_line(cmd, env);	
		free(input_line);
		input_line = NULL;
	}
	free_cmd(&cmd);
	return (0);
}
