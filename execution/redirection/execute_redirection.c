
#include "../execution.h"
#include "redirection.h"

/* Recherche le noeud de commande dans l'arbre AST en traitant les redirections rencontrées */
static t_ast_node	*find_command_node(t_ast_node *ast, t_shell *shell)
{
	t_ast_node	*cmd_node;

	/* Si c'est un nœud de commande, on l'a trouvé */
	if (ast->type == NODE_COMMAND)
		return (ast);
	
	/* Si c'est une redirection, d'abord descendre à gauche */
	if (is_redirection_node(ast))
	{
		/* Descendre récursivement pour trouver le nœud de commande */
		cmd_node = find_command_node(ast->left, shell);
		
		/* Si on a trouvé le nœud de commande, appliquer la redirection en remontant */
		if (cmd_node && process_redirection_node(ast, shell) != 0)
			return (NULL);
		
		return (cmd_node);
	}
	
	/* Sinon, continuer à descendre */
	if (ast->left)
		return (find_command_node(ast->left, shell));
	
	return (NULL);
}

/* Exécute une commande avec des redirections en configurant les descripteurs appropriés */
void	execute_redirection(t_ast_node *ast, t_shell *shell)
{
	int			stdin_copy;
	int			stdout_copy;
	t_ast_node	*cmd_node;

	/* Sauvegarder les descripteurs standard */
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	
	/* Traiter toutes les redirections et trouver le nœud de commande */
	cmd_node = find_command_node(ast, shell);
	
	/* Exécuter la commande si aucune erreur de redirection */
	if (cmd_node)
		execute_ast(cmd_node, shell);
	
	/* Restaurer les descripteurs standard */
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}
