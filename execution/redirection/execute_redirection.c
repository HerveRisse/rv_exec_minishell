
#include "../execution.h"
#include "redirection.h"

/* Recherche le noeud de commande dans l'arbre AST en traitant les redirections rencontrées */
static t_ast_node	*find_command_node(t_ast_node *ast, t_shell *shell)
{
	t_ast_node	*cmd_node;

	cmd_node = ast->left;
	while (cmd_node && cmd_node->type != NODE_COMMAND)
	{
		if (is_redirection_node(cmd_node))
			process_redirection_node(cmd_node, shell);
		cmd_node = cmd_node->left;
	}
	return (cmd_node);
}

/* Restaure les descripteurs standard et ferme les descripteurs de fichier ouverts */
static void	cleanup_descriptors(int stdin_copy, int stdout_copy, int in_fd,
						int out_fd)
{
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

/* Exécute une commande avec des redirections en configurant les descripteurs appropriés */
void	execute_redirection(t_ast_node *ast, t_shell *shell)
{
	int			in_fd;
	int			out_fd;
	int			stdin_copy;
	int			stdout_copy;
	t_ast_node	*cmd_node;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (setup_redirection(ast, &in_fd, &out_fd, shell))
		return ;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	setup_std_descriptors(in_fd, out_fd);
	cmd_node = find_command_node(ast, shell);
	if (cmd_node)
		execute_ast(cmd_node, shell);
	cleanup_descriptors(stdin_copy, stdout_copy, in_fd, out_fd);
}
