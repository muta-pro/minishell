/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:10 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/09 15:03:44 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	file_name(char *buf, int count)
{
	char	*num;

	num = ft_itoa(count);
	ft_strcpy(buf, "/tmp/.minishell_hd_");
	ft_strcat(buf, num);
	free(num);
}

void	read_h_input(char *delim, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("here-doc delimited by EOF\n");
			break ;
		}
		if (strcmp(line, delim) == 0)
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	process_h_node(t_redir *tmp, int *h_count)
{
	char	file[50];
	int		fd;

	if (tmp->type == T_REDIR_HEREDOC)
	{
		file_name(file, (*h_count)++);
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return ; //handle error needing
		read_h_input(tmp->file_name, fd);
		close(fd);
		tmp->type = T_REDIR_IN;
		free(tmp->file_name);
		tmp->file_name = ft_strdup(file);
		return (1);
	}
	return (0);
}

void	here_docs(t_ast_node *node, int *h_count)
{
	t_redir	*tmp;

	if (!node)
		return ;
	if (node->type == NODE_CMND)
	{
		tmp = node->redir_list;
		while (tmp)
		{
			process_h_node(tmp, h_count);
			tmp = tmp->next;
		}
	}
	here_docs(node->left, h_count);
	here_docs(node->right, h_count);
}
