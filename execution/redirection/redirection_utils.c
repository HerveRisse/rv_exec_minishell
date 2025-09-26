
#include "../execution.h"

/* Vérifie si un noeud AST est un noeud de redirection (<, >, >>, <<) */
int	is_redirection_node(t_ast_node *node)
{
	return (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC);
}

/* Configure les descripteurs standard avec les descripteurs de fichier fournis */
void	setup_std_descriptors(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
}

/* Restaure les descripteurs standard à partir des descripteurs temporaires */
void	setup_tmp_descriptors(int tmp_in, int tmp_out)
{
	if (tmp_in != STDIN_FILENO)
	{
		dup2(tmp_in, STDIN_FILENO);
		close(tmp_in);
	}
	if (tmp_out != STDOUT_FILENO)
	{
		dup2(tmp_out, STDOUT_FILENO);
		close(tmp_out);
	}
}

/* Traite un noeud de redirection en configurant les descripteurs appropriés */
void	process_redirection_node(t_ast_node *node, t_shell *shell)
{
	int	tmp_in;
	int	tmp_out;

	tmp_in = STDIN_FILENO;
	tmp_out = STDOUT_FILENO;
	if (setup_redirection(node, &tmp_in, &tmp_out, shell) == 0)
		setup_tmp_descriptors(tmp_in, tmp_out);
}
