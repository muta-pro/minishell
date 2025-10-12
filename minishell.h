/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/10/12 16:36:25 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <string.h>
# include <sys/wait.h>


typedef struct s_cmd
{
	char			**full_cmd;
	// char			*infile;
	// char			*outfile;
	// int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_test
{
	char	*path;
}	t_test;


void	ft_getcwd(t_cmd	*cmd);
void	ft_chdir(t_cmd *cmd);
void	ft_exit(char *exit_status);
void	ft_env(t_env *env);
void	ft_unset(t_env **env, char *str);
void	ft_export(t_env **env, char *str);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);
t_env	*add_new_node(void);

#endif