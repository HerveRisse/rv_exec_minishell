#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../execution.h"
#include "redirection.h"

// fonction utilitaire pour écrire le contenu d'un fichier dans le pipe ou stdout
static int write_file_into_fd(const char *filename, int fd)
{
    int file;
    ssize_t n;
    char buffer[4096];

    file = open(filename, O_RDONLY);
    if (file < 0)
    {
        perror(filename);
        return -1;
    }
    while ((n = read(file, buffer, sizeof(buffer))) > 0)
        write(fd, buffer, n);
    close(file);
    return 0;
}

// Parcours récursif de l'AST pour traiter les redirections d'entrée <
// Garde l'ordre gauche → droite
static int process_input_redirs(t_ast_node *ast, int write_fd)
{
    if (!ast)
        return 0;

    // traite d'abord le left
    if (process_input_redirs(ast->left, write_fd) < 0)
        return -1;

    // puis ce nœud si c'est une redirection d'entrée
    if (ast->type == NODE_REDIR_IN)
    {
        if (write_file_into_fd(ast->filename, write_fd) < 0)
            return -1;
    }

    // puis le right si besoin
    return process_input_redirs(ast->right, write_fd);
}

void execute_redirection(t_ast_node *ast, t_shell *shell)
{
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);
    int fd_out;
    t_ast_node *cmd_node;

    if (!ast)
        return;

    // Traite les redirections de sortie > et >> sur ce niveau
    if (ast->type == NODE_REDIR_OUT)        // >
        fd_out = open(ast->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (ast->type == NODE_APPEND)      // >>
        fd_out = open(ast->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        fd_out = -1;

    if (fd_out >= 0)
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    // Parcours et traite toutes les redirections d'entrée <
    process_input_redirs(ast, STDIN_FILENO);

    // Trouve le nœud de commande et exécute
    cmd_node = ast;
    while (cmd_node && cmd_node->type != NODE_COMMAND)
        cmd_node = cmd_node->left; // descend à gauche
    if (cmd_node)
        execute_ast(cmd_node, shell);

    // Restaure STDIN/STDOUT
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
}
