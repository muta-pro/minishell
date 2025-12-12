/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_docs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:06:10 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/12 17:37:09 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_tmp_hfile(char *file_name)
{
	if (strncmp(file_name, "/tmp/.minishell_hd_", 19) == 0)
		return (1);
	return (0);
}

void	file_name(char *buf, int count)
{
	char	*num;

	num = ft_itoa(count);
	strcpy(buf, "/tmp/.minishell_hd_");
	strcat(buf, num);
	free(num);
}

void	read_h_input(char *delim, int fd)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delim);
	signal(SIGINT, handle_sigint_hrdc);
	while (1)
	{
		line = readline("heredoc>");
		if (g_got_sigint)
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
		{
			printf("Warining: here-doc delimited by EOF\n");
			break ;
		}
		if (line && ft_strncmp(line, delim, len) == 0)
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	signal(SIGINT, handle_sigint);
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
			return (0); //handle error needing
		read_h_input(tmp->file_name, fd);
		close(fd);
		if (g_got_sigint)
		{
			unlink(file);
			return (0);
		}
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
