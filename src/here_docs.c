/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_docs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:06:10 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/12 17:37:09 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expand_h_var(char *line, t_shell *shell)
{
	int		i;
	char	*new_line;

	new_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if ((line[i] == '$') && (line[i + 1] == '?'
				|| ft_isalpha(line[i + 1])))
			handle_dollar(line, &i, &new_line, shell);
		else
			new_line = join_char(new_line, line[i++]);
	}
	return (new_line);
}

void	file_name(char *buf, int count)
{
	char	*num;

	num = ft_itoa(count);
	ft_strcpy(buf, "/tmp/.minishell_hd_");
	ft_strcat(buf, num);
	free(num);
}

static int	break_h(char *line, char *delim)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, delim) == 0)
		return (free(line), 1);
	return (0);
}

void	read_h_input(char *delim, int fd, int no_expand, t_shell *shell)
{
	char	*line;

	g_got_sigint = 0;
	signal(SIGINT, handle_sigint_hrdc);
	while (1)
	{
		line = readline("heredoc>");
		if (g_got_sigint)
			break ;
		if (break_h(line, delim))
			break ;
		expand_h_line(&line, no_expand, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (!line && !g_got_sigint)
		print_eof_warning(delim);
	if (line && g_got_sigint)
		free (line);
	signal(SIGINT, handle_sigint);
}


int	process_h_node(t_redir *tmp, int *h_count, t_shell *shell)
{
	char	file[50];
	int		fd;

	if (tmp->type == T_REDIR_HEREDOC)
	{
		file_name(file, (*h_count)++);
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		read_h_input(tmp->file_name, fd, tmp->no_expand, shell);
		close(fd);
		if (g_got_sigint)
		{
			unlink(file);
			shell->exit_status = 130;
			return (-1);
		}
		tmp->type = T_REDIR_IN;
		free(tmp->file_name);
		tmp->file_name = ft_strdup(file);
		if (!tmp->file_name)
			return (unlink(file), -1);
		return (1);
	}
	return (0);
}

int	here_docs(t_ast_node *node, int *h_count, t_shell *shell)
{
	t_redir	*tmp;
	int		r;

	if (!node)
		return (1);
	if (node->type == NODE_CMND)
	{
		tmp = node->redir_list;
		while (tmp)
		{
			r = process_h_node(tmp, h_count, shell);
			if (r == -1)
				return (0);
			tmp = tmp->next;
		}
	}
	if (!here_docs(node->left, h_count, shell))
		return (0);
	if (!here_docs(node->right, h_count, shell))
		return (0);
	return (1);
}
