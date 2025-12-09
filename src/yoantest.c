#include "shell.h"

t_ast_node *create_command_node(char **args);
void free_ast2(t_ast_node *node);
t_ast_node *test_ls_simple();
t_ast_node *test_pipe_simple();

t_ast_node *create_command_node(char **args)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node) return (NULL);

    node->type = NODE_CMND;
    node->left = NULL;
    node->right = NULL;
    node->redir_list = NULL; // Default to no redirections

    // Count args to allocate the correct size for the copy
    int i = 0;
    while (args[i])
        i++;
    
    node->args = malloc(sizeof(char *) * (i + 1));
    if (!node->args) {
        free(node);
        return (NULL);
    }

    i = 0;
    while (args[i])
    {
        node->args[i] = strdup(args[i]);
        i++;
    }
    node->args[i] = NULL; // NULL-terminate the array

    return (node);
}

void free_ast2(t_ast_node *node)
{
    if (!node) return;
    
    free_ast2(node->left);
    free_ast2(node->right);

    if (node->type == NODE_CMND)
    {
        // Free the args array and the strings inside
        int i = 0;
        while (node->args[i])
        {
            free(node->args[i]);
            i++;
        }
        free(node->args);
        
        // Free the redirection list
        t_redir *current = node->redir_list;
        while (current)
        {
            t_redir *next = current->next;
            free(current->file_name);
            free(current);
            current = next;
        }
    }
    free(node);
}

t_ast_node *test_pipe_simple()
{
    // 1. Create the leaf nodes (the commands)
    char *ls_args[] = {"yes", NULL};
    t_ast_node *ls_node = create_command_node(ls_args);

    char *wc_args[] = {"head", "-n", "5", NULL};
    t_ast_node *wc_node = create_command_node(wc_args);

    // 2. Create the root PIPE node
    t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
    pipe_node->type = NODE_PIPE;
    pipe_node->args = NULL;
    pipe_node->redir_list = NULL;

    // 3. Connect the commands as children of the pipe
    pipe_node->left = ls_node;
    pipe_node->right = wc_node;

    return (pipe_node);
}

t_ast_node *test_ls_simple()
{
    // The command and its arguments
    char *ls_args[] = {"ls", "-l", NULL};
    
    // Create the command node using our helper
    t_ast_node *ls_node = create_command_node(ls_args);

    return (ls_node);
}