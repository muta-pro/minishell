/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/13 15:05:05 by imutavdz      #+#    #+#                 */
/*   Updated: 2025/12/02 19:11:14 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_tmp(t_ast_node *node)
{
	t_redir	*tmp;

	if (!node)
		return ;
	if (node->type == NODE_CMND)
	{
		tmp = node->redir_list;
		while (tmp)
		{
			if (tmp->type == T_REDIR_IN && is_tmp_hfile(tmp->file_name))
				unlink(tmp->file_name);
			tmp = tmp->next;
		}
	}
	clean_tmp(node->left);
	clean_tmp(node->right);
}

int	is_delim(t_token *tok)
{
	if (!tok || tok->type == T_EOF || tok->type == T_PIPE
		|| tok->type == T_LOGIC_OR || tok->type == T_LOGIC_AND)
		return (1);
	return (0);
}

char	*join_char(char *str, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(str, tmp));
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	return (res);
}

void	print_indent(int level)
{
	while (level > 0)
	{
		printf("	");
		level--;
	}
}

void	debug_ast(t_ast_node *node, int level)
{
	t_redir	*tmp;

	tmp = node->redir_list;
	if (!node)
		return ;
	print_indent(level);
	if (node->type == NODE_PIPE)
	{
		printf("\033[1;35m[PIPE]\033[0m\n"); // Purple
		debug_ast(node->left, level + 1);
		debug_ast(node->right, level + 1);
	}
	// 2. Handle COMMAND Nodes
	else if (node->type == NODE_CMND)
	{
		printf("\033[1;32m[CMD]\033[0m "); // Green        
		// Print command arguments (e.g., "cat", "-e")
		if (node->args)
		{
		    int i = 0;
		    while (node->args[i])
		    {
		        printf("[%s] ", node->args[i]);
		        i++;
		    }
		    printf("\n");
		    print_indent(level + 1);
		    printf("\033[33m[EXPANDED] Arguments clean and ready.\033[0m");
		}
	}
	   // Print Redirections (The important part for you!)
	   tmp = node->redir_list;
	   while (tmp)
	   {
	       if (tmp->type == T_REDIR_HEREDOC)
	       {
	           // This means it hasn't been processed yet
	           printf("\n");
	           print_indent(level + 1);
	           if (tmp->no_expand)
	           	printf("\033[1;31m<< [HEREDOC] Delimiter: %s (NO EXPANSION)\033[0m", tmp->file_name);
	           else
	           	printf("\033[1;31m<< [HEREDOC] Delimiter: %s (EXPANDS VARS)\033[0m", tmp->file_name);
	       }
	       else if (tmp->type == T_REDIR_IN)
	       {
	           // It's an input redirection. Check if it's ours or a user file.
	           printf("\n");
	           print_indent(level + 1);
	           if (ft_strncmp(tmp->file_name, "/tmp/.minishell_hd_", 19) == 0)
	               printf("\033[1;36m<  [TEMP FILE] Path: %s\033[0m", tmp->file_name);
	           else
	               printf("\033[1;34m<  [INPUT FILE] Path: %s\033[0m", tmp->file_name);
	       }
	       else if (tmp->type == T_REDIR_OUT || tmp->type == T_REDIR_APPEND)
	       {
	           printf("\n");
	           print_indent(level + 1);
	           if (tmp->type == T_REDIR_APPEND)
	           	printf("\033[1;34m>  [APPEND] Path: %s\033[0m", tmp->file_name);
	           else
	           	printf("\033[1;34m>  [OUTPUT] Path: %s\033[0m", tmp->file_name);
	       }
	       tmp = tmp->next;
	   }
	   printf("\n");
}
// void read_q_input(char *delim, int fd); //for open singl-quotes
// void read_cmnd_input(char *delim, int fd); //for unfinished cmnd
