/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:07:01 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/19 13:10:24 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHELL_H
# define SHELL_H
/*Heredoc handling is complex and involves multiple phases:

Tokenizer: recognize <<
Parser: identify the delimiter
Executor: read lines until delimiter
Expander: expand variables if delimiter wasn't quoted*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_heredoc
{
	char	*delimiter;
	int		expand;
}	t_heredoc;

char	**copy_envp(char **envp);
int		init_shlvl(char **envp);
int		update_env_var(char ***envp, char *key, char *value);
char	*new_env_str(char *key, char *value);
void	**free_envp(char **envp);//cleanup
int		find_env_varible(char **envp, char *key);
char	*get_env_var(char **envp, char *key);//read var value
void	unset_env_var(char ***envp, char *key);//remove var

void	print_tokens(t_token *tokens);

//check characters
int		is_operator_char(char c);
int		is_whitespace(char c);
int		is_quote(char c);
int		is_redirection(char c);
int		valid_char(char c);
int		null_terminator(char c);

//SIGNALS
// static void	install_parent_handler(void);

#endif