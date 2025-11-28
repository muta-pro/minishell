/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:54:35 by imutavdz          #+#    #+#             */
/*   Updated: 2025/11/28 16:32:09 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DEFINES_H
# define DEFINES_H

# define DEFAULT_ERR "shell_error: "
# define ARG_ERR "too many arguments" //for builtins cmnd exit or export
# define NUM_ERR "missing numeric aguments" //same
# define PERM_DEN "permission denied" //cd
# define IS_DIR "is a directory"
# define NOT_DIR "is not a directory"
# define NOT_EX "file or directory doesn't exist"
# define SYTX_ERR "Syntax error: "

# define EMALLOC -1
# define ERROR 1
# define SUCCESS 0

# define PATH_MAX 4096 //buff alloc for paths
# define DECLARE "declare -x" //str used by export builtin to format output

#endif