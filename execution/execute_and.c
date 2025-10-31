
#include "execution.h"

/* Exécute les commandes reliées par && (exécute la droite seulement si la gauche réussit) */
void	execute_and(t_ast_node *ast, t_shell *shell)
{
	execute_ast(ast->left, shell);
	if (shell->exit_status == 0)
		execute_ast(ast->right, shell);
}
