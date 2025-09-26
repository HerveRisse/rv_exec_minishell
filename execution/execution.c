
#include "execution.h"

/* Exécute un noeud de l'arbre syntaxique abstrait en fonction de son type */
void	execute_ast(t_ast_node *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
		execute_command(ast, shell, STDIN_FILENO, STDOUT_FILENO);
	else if (ast->type == NODE_PIPE)
		execute_pipe(ast, shell);
	else if (ast->type == NODE_AND)
		execute_and(ast, shell);
	else if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_APPEND || ast->type == NODE_HEREDOC)
		execute_redirection(ast, shell);
}
