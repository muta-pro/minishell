/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/10/12 18:40:39 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_execve(t_env *env, char **full_cmd, t_cmd *cmd);

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
		if (pid == -1)
		{
			perror("fork fail");
			return ;
		}
		if (!pid)
		{
			test_execve(env, cmd->full_cmd, cmd);
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
	(*env)->next = NULL;
	*env = start;
}

void free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		free(temp->full_cmd);
		free(temp);
	}
}

void free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
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
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		env_array[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

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
char	*find_path(char **split_paths, char *cmd)
{
	int		i;
	char	*current_path;
	char	*temp;

	if (!split_paths)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		temp = ft_strjoin(split_paths[i], "/");
		current_path = ft_strjoin(temp, cmd);
		free(temp);
		if (current_path && access(current_path, F_OK | X_OK) == 0)
			return (current_path);
		free(current_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **twoDenv, char *cmd)
{
	int		i = 0;
	char	*paths;
	char	**split_paths;
	char	*full_path;

	paths = NULL;
	while (twoDenv && twoDenv[i])
	{
		if (!(strncmp("PATH=", twoDenv[i], 5)))
		{
			paths = ft_strdup(twoDenv[i] + 5);
			if (!paths)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, ':');
	free(paths);
	full_path = find_path(split_paths, cmd);
	if (!full_path)
		return (free_arr(split_paths), NULL);
	return (free_arr(split_paths), full_path);
}

void	test_execve(t_env *env, char **full_cmd, t_cmd *cmd)	
{
	char	**twoDenv;
	char	*path;
	
	path = NULL;
	twoDenv = list_to_2d(env);
	path = get_path(twoDenv, full_cmd[0]);
	if (execve(path, full_cmd, twoDenv) == -1)
	{
		free_arr(twoDenv);
		free(path);
		free_env(&env);
		free_cmd(&cmd);
		exit(0); // handle exit
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char 	*input_line;
	t_cmd	*cmd;
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (0);
	build_env(envp, &env);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free(env), 0);
	cmd->next = NULL;
	while (cmd)
	{
		input_line = readline("minishell> ");
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
	free_env(&env);
	return (0);	
}
