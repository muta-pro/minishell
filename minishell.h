/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 16:23:13 by yneshev       #+#    #+#                 */
/*   Updated: 2025/06/23 19:52:30 by yneshev       ########   odam.nl         */
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

typedef struct s_cmd
{
	char			*input_line;
	char			**full_cmd;
	// char			*infile;
	// char			*outfile;
	// int				pipe;
	struct s_cmd	*next;
}	t_cmd;

void	ft_getcwd(t_cmd	*cmd);
void	ft_chdir(t_cmd *cmd);
void	ft_exit(char *exit_status);

#endif