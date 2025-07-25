/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 20:35:10 by yneshev       #+#    #+#                 */
/*   Updated: 2025/07/25 16:10:14 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(t_cmd *cmd, t_env *env)
{
	if (!(strncmp(cmd->full_cmd[0], "cd", 2)))
	{
		ft_chdir(cmd);
	}
	if (!(strcmp(cmd->full_cmd[0], "pwd")))
		ft_getcwd(cmd);
	if (!(strncmp("exit", cmd->full_cmd[0], 4)))
		ft_exit(cmd->full_cmd[0] + 5);
	if (!(strncmp("env", cmd->full_cmd[0], 3)))
		ft_env(env);
	if (!(strncmp("export ", cmd->full_cmd[0], 7)))
		ft_export(&env, cmd->full_cmd[0] + 7);
	if (!(strncmp("unset ", cmd->full_cmd[0], 6)))
		ft_unset(&env, cmd->full_cmd[0] + 6);
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
		c = 1;
		while (envp[i][j] && c++)
			j++;
		(*env)->value = strndup(envp[i] + j - c + 2, c - 2);
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
		return (0);
	cmd->next = NULL;
	while (cmd)
	{
		input_line = readline("minishell> ");
		cmd->input_line = input_line;
		cmd->full_cmd = &input_line;
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
	return (0);
}
