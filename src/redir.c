/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/07 15:49:06 by yneshev       #+#    #+#                 */
/*   Updated: 2025/12/07 17:06:15 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int apply_redir(t_redir *node)
{
    int fd;
    while (node)
    {
        if (node->type == T_REDIR_OUT || node->type == T_REDIR_APPEND)
        {
            if (node->type == T_REDIR_OUT)
                fd = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd = open(node->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror(node->file_name);
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (node->type == T_REDIR_IN)
        {
            fd = open(node->file_name, O_RDONLY);
            if (fd == -1)
            {
                perror(node->file_name);
                return (-1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        node = node->next;
    }
    return (0);
}
