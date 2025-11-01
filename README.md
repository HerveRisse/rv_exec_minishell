
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../execution.h"
#include "redirection.h"

static t_ast_node *find_command_node(t_ast_node *ast)
{
    if (!ast)
        return NULL;
    if (ast->type == NODE_COMMAND)
        return ast;
    if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT ||
        ast->type == NODE_APPEND || ast->type == NODE_HEREDOC)
        return find_command_node(ast->left);
    if (ast->left)
        return find_command_node(ast->left);
    return NULL;
}

// Écrit tout le contenu des fichiers d'entrée (<) dans le pipe
static int fill_pipe_with_inputs(t_ast_node *ast, int write_fd)
{
    char buffer[4096];
    ssize_t n;
    int fd;

    if (!ast)
        return 0;

    // Parcours d'abord le left
    fill_pipe_with_inputs(ast->left, write_fd);

    // Puis traite ce nœud si c'est une redirection d'entrée
    if (ast->type == NODE_REDIR_IN)
    {
        fd = open(ast->filename, O_RDONLY);
        if (fd < 0)
        {
            perror(ast->filename);
            return -1;
        }
        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            write(write_fd, buffer, n);
        close(fd);
    }

    // Ensuite parcours right si nécessaire
    fill_pipe_with_inputs(ast->right, write_fd);

    return 0;
}

void execute_redirection(t_ast_node *ast, t_shell *shell)
{
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);
    t_ast_node *cmd_node = find_command_node(ast);
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    // Remplit le pipe avec tous les fichiers d'entrée
    if (fill_pipe_with_inputs(ast, pipefd[1]) != 0)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }
    close(pipefd[1]); // Fermeture côté écriture

    // Redirige STDIN vers le read-end du pipe
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    if (cmd_node)
        execute_ast(cmd_node, shell);

    // Restaurer STDIN et STDOUT
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
}
