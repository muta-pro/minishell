/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:54:35 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/22 04:08:42 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WRITE_STR(str) write(STDERR_FILENO, str, ft_strlen(str))
# define SHELL_NAME "minishell: "
# define ARG_ERR "too many arguments" //Used as the msg argument for builtins cmnd fail
# define NUM_ERR "missing numeric aguments" //same (e.g., print_shell_err("exit", NUM_ERR, 255)).
# define PERM_DEN "permission denied" //cd
# define IS_DIR "is a directory"
# define NOT_DIR "is not a directory"
# define NOT_EX "file or directory doesn't exist"
# define SYTX_ERR "Syntax error: "
# define NO_CMND "Command not found."

# define EMALLOC -1
# define ERROR 1
# define SUCCESS 0

# define PATH_MAX 4096 //buff alloc for paths
# define DECLARE "declare -x" //str used by export builtin to format output

#endif